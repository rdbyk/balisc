/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "dynamic_modules.hxx"
#include "context.hxx"
#include "configvariable.hxx"

extern "C"
{
#include "loadOnUseClassPath.h"
#include "sci_malloc.h"
}

#include <libxml/xpath.h>
#include <libxml/xmlreader.h>

struct GatewayStr
{
    GatewayStr()
    {
        wstName.clear();
        wstFunction.clear();
        iType = types::Function::EntryPointOldC;
    }

    std::wstring wstName;
    std::wstring wstFunction;
    types::Function::FunctionType iType;
};

typedef std::vector<GatewayStr> vectGateway;

vectGateway loadGatewaysName(const std::wstring& _wstModuleName)
{
    vectGateway vect;
    
    std::wstring wstModuleName = ConfigVariable::getSCIPath();
    wstModuleName += L"/modules/";
    wstModuleName += _wstModuleName;
    wstModuleName += L"/sci_gateway/";
    wstModuleName += _wstModuleName;
    wstModuleName += L"_gateway.xml";

    char* pstModuleName = wide_string_to_UTF8(wstModuleName.c_str());

    /* Don't care about line return / empty line */
    xmlKeepBlanksDefault(0);
    // parse file
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtxt = NULL;
    xmlXPathObjectPtr xpathObj = NULL;

    doc = xmlParseFile(pstModuleName);
    if (doc == NULL)
    {
        std::cout << "Error: Could not parse file " << pstModuleName << std::endl;
        FREE(pstModuleName);
        return vect;
    }
    FREE(pstModuleName);

    xpathCtxt = xmlXPathNewContext(doc);
    xpathObj = xmlXPathEval((const xmlChar*)"//module/gateway", xpathCtxt);
    if (xpathObj && xpathObj->nodesetval->nodeMax)
    {
        /* the Xpath has been understood and there are node */
        for (int	i = 0 ; i < xpathObj->nodesetval->nodeNr ; i++)
        {
            GatewayStr str;

            xmlAttrPtr attrib = xpathObj->nodesetval->nodeTab[i]->properties;
            /* Get the properties of <module>  */
            while (attrib != NULL)
            {
                /* loop until when have read all the attributes */
                if (xmlStrEqual(attrib->name, (const xmlChar*)"name"))
                {
                    wchar_t * ws = to_wide_string((const char*)attrib->children->content);
                    str.wstName = ws;
                    FREE(ws);
                }
                else if (xmlStrEqual(attrib->name, (const xmlChar*)"function"))
                {
                    wchar_t * ws = to_wide_string((const char*)attrib->children->content);
                    str.wstFunction = ws;
                    FREE(ws);
                }
                else if (xmlStrEqual(attrib->name, (const xmlChar*)"type"))
                {
                    str.iType = (types::Function::FunctionType)atoi((const char*)attrib->children->content);
                }
                attrib = attrib->next;
            }
            vect.push_back(str);
        }
    }

    if (xpathObj)
    {
        xmlXPathFreeObject(xpathObj);
    }

    if (xpathCtxt)
    {
        xmlXPathFreeContext(xpathCtxt);
    }

    xmlFreeDoc(doc);

    return vect;
}

// GenericModule
int GenericModule::Load(const wchar_t wcsPath[], const wchar_t wcsModule[], dynlib_name_format iFormat, types::Function::LOAD_DEPS pLoadDeps)
{
    std::wstring wstPath(wcsPath);
    std::wstring wstModuleName(wcsModule);
    wchar_t* pwstLibName = buildModuleDynLibraryNameW(wstModuleName.c_str(), iFormat);
    vectGateway vect = loadGatewaysName(wstPath);
    symbol::Context* pCtx = symbol::Context::getInstance();

    for (int i = 0 ; i < (int)vect.size() ; i++)
    {
        pCtx->addFunction(types::Function::createFunction(vect[i].wstFunction, vect[i].wstName, pwstLibName, vect[i].iType, pLoadDeps, wstPath));
    }

    FREE(pwstLibName);
    return 1;
}

int GenericModule::Load(const wchar_t wcsModule[], dynlib_name_format iFormat, types::Function::LOAD_DEPS pLoadDeps)
{
    return GenericModule::Load(wcsModule, wcsModule, iFormat, pLoadDeps);
}

//Scinotes module
bool ScinotesModule::loadedDep = false;
int ScinotesModule::LoadDeps(const std::wstring& /*_functionName*/)
{
    if (loadedDep == false)
    {
        loadOnUseClassPath("SciNotes");
        loadedDep = true;
    }

    return 1;
}

int ScinotesModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"scinotes", DYNLIB_NAME_FORMAT_2, &ScinotesModule::LoadDeps);
#else
    return GenericModule::Load(L"scinotes", DYNLIB_NAME_FORMAT_3, &ScinotesModule::LoadDeps);
#endif
}

//Functions module
int FunctionsModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"functions", L"functions_gw", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"functions", DYNLIB_NAME_FORMAT_3);
#endif
}

int StatisticsModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"statistics", L"statistics_gw", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"statistics", DYNLIB_NAME_FORMAT_3);
#endif
}

int SignalProcessingModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"signal_processing", L"signal_processing_gw", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"signal_processing", DYNLIB_NAME_FORMAT_3);
#endif
}

int HelptoolsModule::LoadDeps(const std::wstring& /*_functionName*/)
{
    if (loadedDep == false)
    {
        loadOnUseClassPath("documentationGeneration");
        loadedDep = true;
    }

    return 1;
}

bool HelptoolsModule::loadedDep = false;
int HelptoolsModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"helptools", DYNLIB_NAME_FORMAT_1, &HelptoolsModule::LoadDeps);
#else
    return GenericModule::Load(L"helptools", DYNLIB_NAME_FORMAT_3, &HelptoolsModule::LoadDeps);
#endif
}

int MatioModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"matio", L"matio_gw", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"matio", DYNLIB_NAME_FORMAT_3);
#endif
}

int Hdf5Module::Load()
{
#ifdef _MSC_VER
    wchar_t* pwstLibName = buildModuleDynLibraryNameW(wstModuleName.c_str(), DYNLIB_NAME_FORMAT_2);
#else
    return GenericModule::Load(L"hdf5", DYNLIB_NAME_FORMAT_3);
#endif
}

int ActionBindingModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"action_binding", L"action_binding_gw", DYNLIB_NAME_FORMAT_2);
#else
    return GenericModule::Load(L"action_binding", DYNLIB_NAME_FORMAT_3);
#endif
}

int SpreadsheetModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"spreadsheet", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"spreadsheet", DYNLIB_NAME_FORMAT_3);
#endif
}

int InterpolationModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"interpolation", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"interpolation", DYNLIB_NAME_FORMAT_3);
#endif
}

int SoundModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"sound", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"sound", DYNLIB_NAME_FORMAT_3);
#endif
}

int RandlibModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"randlib", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"randlib", DYNLIB_NAME_FORMAT_3);
#endif
}

int UmfpackModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"umfpack", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"umfpack", DYNLIB_NAME_FORMAT_3);
#endif
}

int OptimizationModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"optimization", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"optimization", DYNLIB_NAME_FORMAT_3);
#endif
}

int SpecialFunctionsModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"special_functions", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"special_functions", DYNLIB_NAME_FORMAT_3);
#endif
}

int GraphicExportModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"graphic_export", DYNLIB_NAME_FORMAT_2);
#else
    return GenericModule::Load(L"graphic_export", DYNLIB_NAME_FORMAT_3);
#endif
}

int ArnoldiModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"arnoldi", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"arnoldi", DYNLIB_NAME_FORMAT_3);
#endif
}

int CallScilabModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"call_scilab", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"call_scilab", DYNLIB_NAME_FORMAT_3);
#endif
}

int CompletionModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"completion", DYNLIB_NAME_FORMAT_2);
#else
    return GenericModule::Load(L"completion", DYNLIB_NAME_FORMAT_3);
#endif
}

int XmlModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"xml", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"xml", DYNLIB_NAME_FORMAT_3);
#endif
}

int ScicosModule::Load()
{
    std::wstring wstModuleName = L"scicos";

    if (getScilabMode() == SCILAB_NWNI)
    {
        wstModuleName += L"-cli";
    }

#ifdef _MSC_VER
    return GenericModule::Load(L"scicos", wstModuleName.c_str(), DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"scicos", wstModuleName.c_str(), DYNLIB_NAME_FORMAT_3);
#endif
}

bool XcosModule::loadedDep = false;
int XcosModule::LoadDeps(const std::wstring& _functionName)
{
    if (loadedDep == false && _functionName != L"closeXcos")
    {
        loadOnUseClassPath("Xcos");
        loadedDep = true;
    }

    return 1;
};

int XcosModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"xcos", DYNLIB_NAME_FORMAT_2, &XcosModule::LoadDeps);
#else
    return GenericModule::Load(L"xcos", DYNLIB_NAME_FORMAT_3, &XcosModule::LoadDeps);
#endif
}

int MPIModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"mpi", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"mpi", DYNLIB_NAME_FORMAT_3);
#endif
}

int ExternalObjectsModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"external_objects", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"external_objects", DYNLIB_NAME_FORMAT_3);
#endif
}

int ExternalObjectsJavaModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"external_objects_java", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"external_objects_java", DYNLIB_NAME_FORMAT_3);
#endif
}

int SlintModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"slint", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"slint", DYNLIB_NAME_FORMAT_3);
#endif
}

bool GraphicsModule::loadedDep = false;
int GraphicsModule::LoadDeps(const std::wstring& /*_functionName*/)
{
    if (loadedDep == false)
    {
        loadOnUseClassPath("graphics");
        loadedDep = true;
    }

    return 1;
}

int GraphicsModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"graphics", DYNLIB_NAME_FORMAT_1, &GraphicsModule::LoadDeps);
#else
    return GenericModule::Load(L"graphics", DYNLIB_NAME_FORMAT_3, &GraphicsModule::LoadDeps);
#endif
}


bool GuiModule::loadedDep = false;
int GuiModule::LoadDeps(const std::wstring& _functionName)
{
    if (loadedDep == false &&
            (_functionName == L"uicontrol" ||
             _functionName == L"uimenu" ||
             _functionName == L"usecanvas" ||
             _functionName == L"loadGui" ||
             _functionName == L"figure"))
    {
        loadOnUseClassPath("graphics");
        loadedDep = true;
    }

    return 1;
}
int GuiModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"gui", DYNLIB_NAME_FORMAT_2, &GuiModule::LoadDeps);
#else
    return GenericModule::Load(L"gui", DYNLIB_NAME_FORMAT_3, &GuiModule::LoadDeps);
#endif
}

int JvmModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"jvm", L"libjvm", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"jvm", DYNLIB_NAME_FORMAT_3);
#endif
}

int UiDataModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"ui_data", DYNLIB_NAME_FORMAT_2);
#else
    return GenericModule::Load(L"ui_data", DYNLIB_NAME_FORMAT_3);
#endif
}

int TclsciModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"tclsci", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"tclsci", DYNLIB_NAME_FORMAT_3);
#endif
}

int HistoryBrowserModule ::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"history_browser", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"history_browser", DYNLIB_NAME_FORMAT_3);
#endif
}

int WebtoolsModule::Load()
{
#ifdef _MSC_VER
    return GenericModule::Load(L"webtools", DYNLIB_NAME_FORMAT_1);
#else
    return GenericModule::Load(L"webtools", DYNLIB_NAME_FORMAT_3);
#endif
}
