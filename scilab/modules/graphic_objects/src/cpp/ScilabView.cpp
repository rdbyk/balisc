/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011-2011 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include <iostream>
#include <map>
#include <list>
#include <cstring>

#include "internal.hxx"
#include "ScilabView.hxx"
#include "CallGraphicController.hxx"
#include "returnProperty.h"

extern "C"
{
#include "CurrentObject.h"
#include "createGraphicObject.h"
#include "setGraphicObjectProperty.h"
#include "getGraphicObjectProperty.h"
#include "graphicObjectProperties.h"
#include "deleteGraphicObject.h"
#include "sci_malloc.h"
}

/**
 * C Wrapping functions
 * \{
 */
void ScilabNativeView__createObject(int iUID)
{
    ScilabView::createObject(iUID);
}

void ScilabNativeView__deleteObject(int iUID)
{
    ScilabView::deleteObject(iUID);
}

void ScilabNativeView__updateObject(int iUID, int iProperty)
{
    ScilabView::updateObject(iUID, iProperty);
}

void ScilabNativeView__setCurrentFigure(int iUID)
{
    ScilabView::setCurrentFigure(iUID);
}

void ScilabNativeView__setCurrentSubWin(int iUID)
{
    ScilabView::setCurrentSubWin(iUID);
}

void ScilabNativeView__setCurrentObject(int iUID)
{
    ScilabView::setCurrentObject(iUID);
}

int ScilabNativeView__getValidDefaultFigureId()
{
    return ScilabView::getValidDefaultFigureId();
}

int ScilabNativeView__getFigureFromIndex(int figNum)
{
    return ScilabView::getFigureFromIndex(figNum);
}

/**
 * \}
 */

void ScilabView::createObject(int iUID)
{
    //std::cerr << "[ScilabView] ++ createObject UID=" << iUID << std::endl;
    int iType = -1;
    int *piType = &iType;

    getGraphicObjectProperty(iUID, __GO_TYPE__, jni_int, (void **)&piType);
    if (iType == __GO_FIGURE__)
    {
        m_figureList[iUID] = -1;
        setCurrentFigure(iUID);
    }

    // Register object handle.
    getObjectHandle(iUID);

    PathItem* item = new PathItem();
    item->uid = iUID;

    m_pathList[iUID] = item;

    m_userdata[iUID]; //create an empty vector<int>

    //get existing information from current object
    updateObject(iUID, __GO_PARENT__);
    updateObject(iUID, __GO_CHILDREN__);
    updateObject(iUID, __GO_TAG__);
}

void ScilabView::deleteObject(int iUID)
{
    //std::cerr << "[ScilabView] -- deleteObject UID=" << iUID << std::endl;
    int iType = -1;
    int *piType = &iType;
    int iParentUID = 0;

    /* get USEr_DATA property and free it*/
    int iUserDataSize = 0;
    int *piUserDataSize = &iUserDataSize;
    int *piUserData = NULL;
    getGraphicObjectProperty(iUID, __GO_USER_DATA_SIZE__, jni_int, (void **)&piUserDataSize);
    getGraphicObjectProperty(iUID, __GO_USER_DATA__, jni_int_vector, (void **)&piUserData);

    if (piUserData && piUserDataSize)
    {
        types::InternalType* pUD = (types::InternalType*)sciReturnUserData(piUserData, iUserDataSize);
        pUD->DecreaseRef();
        pUD->killMe();
    }
    /*
    ** If deleting a figure, remove from figure list.
    */
    m_figureList.erase(iUID);

    /*
    ** If deleting current figure find another current one,
    ** if there is no more figure : NULL
    */
    if (m_currentFigure == iUID) // Deleting current figure
    {
        int iAxesUID = 0;
        int* piAxesUID = &iAxesUID;

        if (getNbFigure() != 0)
        {
            m_currentFigure = m_figureList.begin()->first;
            getGraphicObjectProperty(m_currentFigure, __GO_SELECTED_CHILD__, jni_int,  (void**)&piAxesUID);
            setCurrentSubWin(iAxesUID);
        }
        else
        {
            setCurrentFigure(0);
            setCurrentSubWin(0);
        }
    }

    /*
    ** If deleting current entity, set parent as new current.
    */
    if (m_currentObject == iUID) // Deleting current object
    {
        iParentUID = getParentObject(iUID);
        setCurrentObject(iParentUID);
    }

    // Remove the corresponding handle.
    __handleList_iterator it = m_handleList.find(iUID);
    if (it != m_handleList.end())
    {
        m_uidList.erase(it->second);
        m_handleList.erase(it);
    }

    deleteDataObject(iUID);

    /*clear userdata object*/
    m_userdata.erase(iUID);

    //clear path object
    __pathList_iterator itPath = m_pathList.find(iUID);
    if (itPath != m_pathList.end())
    {
        delete itPath->second; //destroy PathItem object
        m_pathList.erase(itPath); //remove entry
    }
}

void ScilabView::updateObject(int iUID, int iProperty)
{
    //std::cerr << "[ScilabView] == updateObject UID=" << iUID << " PROPERTY=" << pstProperty << std::endl;

    /*
    ** Take care of update if the value update is ID and object type is a Figure I manage.
    */
    switch (iProperty)
    {
        case __GO_ID__ :
        {
            if (m_figureList.find(iUID) != m_figureList.end())
            {
                int iNewId = 0;
                int *piNewId = &iNewId;

                getGraphicObjectProperty(iUID, __GO_ID__, jni_int, (void **)&piNewId);

                m_figureList[iUID] = iNewId;
                //std::cerr << "### [ScilabView] updateMap UID=" << iUID << " id=" << iNewId << std::endl;
            }
            break;
        }
        case __GO_CHILDREN__ :
        {
            int childrenCount = 0;
            int* pChildrenCount = &childrenCount;
            getGraphicObjectProperty(iUID, __GO_CHILDREN_COUNT__, jni_int, (void**)&pChildrenCount);

            __pathList_iterator it = m_pathList.find(iUID);
            if (it != m_pathList.end())
            {
                //update existing item

                PathItem* item = (*it).second;
                //reset children
                item->children.clear();
                if (childrenCount != 0)
                {
                    int* children = NULL;
                    getGraphicObjectProperty(iUID, __GO_CHILDREN__, jni_int_vector, (void**)&children);
                    item->children.assign(children, children + childrenCount);
                    releaseGraphicObjectProperty(__GO_CHILDREN__, children, jni_int_vector, childrenCount);
                }
            }
            break;
        }
        case __GO_PARENT__ :
        {
            int iParent = 0;
            int* piParent = &iParent;
            getGraphicObjectProperty(iUID, __GO_PARENT__, jni_int, (void**)&piParent);

            __pathList_iterator it = m_pathList.find(iUID);

            if (it != m_pathList.end())
            {
                //update existing item

                PathItem* item = (*it).second;
                item->parent = iParent;
            }
            break;
        }
        case __GO_TAG__ :
        {
            int iType = 0;
            int* piType = &iType;
            getGraphicObjectProperty(iUID, __GO_TYPE__, jni_int, (void**)&piType);

            char* tag = NULL;
            getGraphicObjectProperty(iUID, __GO_TAG__, jni_string, (void**)&tag);

            if (tag[0] != 0 && iType == __GO_FIGURE__)
            {
                //not empty string

                //add figure in list of path starter
                m_pathFigList[tag] = iUID;
            }

            __pathList_iterator it = m_pathList.find(iUID);

            if (it != m_pathList.end())
            {
                //update existing item

                PathItem* item = (*it).second;
                item->tag = tag;
                delete[] tag;
            }
            break;
        }
        default:
            break;
    }
}

/*
** Register ScilabView to Controller.
** Must be done after Graphics models are created.
*/
void ScilabView::registerToController(void)
{
    org_scilab_modules_graphic_objects::CallGraphicController::registerScilabView(getScilabJavaVM());
}

/*
** Reove ScilabView from Controller.
*/
void ScilabView::unregisterToController(void)
{
    org_scilab_modules_graphic_objects::CallGraphicController::unregisterScilabView(getScilabJavaVM());
}

int ScilabView::search_path(char* _pstPath)
{
    //copy string to protect it against strtok
    char* pstPath = strdup(_pstPath);
    std::list<int> ignoredList;
    PathItem* path = NULL;
    char* pstSubPath = strtok(pstPath, "/");
    bool bDeep = false;
    while (pstSubPath != NULL)
    {
        if (pstSubPath[0] == 0)
        {
            //"" ?
            break;
        }

        if (pstSubPath[0] != '*')
        {
            //search in direct children
            if (path == NULL)
            {
                path = ScilabView::getFigureItem(pstSubPath);
                if (path == NULL)
                {
                    path = ScilabView::getItem(pstSubPath, ignoredList);
                    if (path == NULL)
                    {
                        break;
                    }
                }

                //if figure is in ignore list, reeturn not found
                if (std::find(ignoredList.begin(), ignoredList.end(), path->uid) != ignoredList.end())
                {
                    return 0;
                }
            }
            else
            {
                PathItem* newPath = search_children(path, pstSubPath, bDeep, ignoredList);
                if (newPath == NULL)
                {
                    //flag handle to ignore and restart parsing
                    ignoredList.push_back(path->uid);
                    pstPath = strdup(_pstPath);
                    pstSubPath = strtok(pstPath, "/");
                    path = NULL;
                    continue;
                }
                else
                {
                    path = newPath;
                }

                bDeep = false;
            }
        }
        else
        {
            //search in all path children
            bDeep = true;
        }

        pstSubPath = strtok(NULL, "/");
    }

    if (path == NULL)
    {
        return 0;
    }

    free(pstPath);
    return path->uid;
}

PathItem* ScilabView::search_children(PathItem* _path, std::string _subPath, bool _bDeep, std::list<int>& _ignoredList)
{
    PathItem::__child_iterator it = _path->children.begin();
    for (; it != _path->children.end() ; ++it)
    {
        PathItem* child = ScilabView::getItem(*it);
        if (child->tag == _subPath)
        {
            bool ignored = false;
            //check if this handle is not in ignoredList
            if (std::find(_ignoredList.begin(), _ignoredList.end(), child->uid) == _ignoredList.end())
            {
                return child;
            }
        }
        else if (_bDeep)
        {
            PathItem *item = search_children(child, _subPath, _bDeep, _ignoredList);
            if (item)
            {
                return item;
            }
        }
    }

    return NULL;
}

std::string ScilabView::get_path(int uid)
{
    PathItem* item = getItem(uid);
    if (item->tag == "")
    {
        //impossible to create a useful path from object without tag
        return "";
    }

    std::string path = item->tag;

    while (item->parent != 0)
    {
        item = getItem(item->parent);
        if (item->tag == "")
        {
            if (path[0] == '*')
            {
                //we have already */ just continue
                continue;
            }
            else
            {
                //add */ instead of /
                path = "*/" + path;
            }
        }
        else
        {
            path = item->tag + "/" + path;
        }
    }

    if (path[0] == '*')
    {
        //path must start by mane
        return "";
    }

    return path;
}

/*
** Allocate static class variable.
*/
ScilabView::__figureList ScilabView::m_figureList;
ScilabView::__handleList ScilabView::m_handleList;
ScilabView::__uidList ScilabView::m_uidList;
long ScilabView::m_topHandleValue = 0;
int ScilabView::m_currentFigure;
int ScilabView::m_currentObject;
int ScilabView::m_currentSubWin;
int ScilabView::m_figureModel;
int ScilabView::m_axesModel;
ScilabView::__pathList ScilabView::m_pathList;
ScilabView::__pathFigList ScilabView::m_pathFigList;
ScilabView::__userdata ScilabView::m_userdata;
