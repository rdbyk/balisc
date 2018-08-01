/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Antoine ELIAS
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

#include <cstring>
#include <sstream>
#include "exp.hxx"
#include "string.hxx"
#include "list.hxx"
#include "tlist.hxx"
#include "listundefined.hxx"
#include "callable.hxx"
#include "polynom.hxx"
#include "overload.hxx"
#include "configvariable.hxx"
#include "types_tools.hxx"
#include "scilabWrite.hxx"

#ifndef NDEBUG
#include "inspector.hxx"
#endif

extern "C"
{
#include "os_string.h"
}

namespace types
{
/**
** Constructor & Destructor (public)
*/
TList::TList() : List()
{
#ifndef NDEBUG
    Inspector::addItem(this);
#endif
}

TList::~TList()
{
#ifndef NDEBUG
    Inspector::removeItem(this);
#endif
}

bool TList::getMemory(int* _piSize, int* _piSizePlusType)
{
    *_piSize = 0;
    *_piSizePlusType = 0;
    for (auto pData : *m_plData)
    {
        int piS, piSPT;
        if (pData->getMemory(&piS, &piSPT))
        {
            *_piSize += piS;
            *_piSizePlusType += piSPT;
        }
    }

    *_piSizePlusType += sizeof(TList);
    return true;
}

/**
** Clone
** Create a new List and Copy all values.
*/
TList* TList::clone()
{
    return new TList(this);
}

bool TList::exists(const std::wstring& _sKey)
{
    return getFieldIndex(_sKey) != -1;
}

bool TList::invoke(typed_list & in, optional_list & /*opt*/, int _iRetCount, typed_list & out, const ast::Exp & e)
{
    if (in.size() == 0)
    {
        out.push_back(this);
        return true;
    }
    else if (in.size() == 1)
    {
        InternalType * arg = in[0];
        InternalType * _out = NULL;
        if (arg->isDouble() || arg->isInt() || arg->isBool() || arg->isImplicitList() || arg->isColon() || arg->isDollar())
        {
            _out = List::extract(&in);
            if (_out == NULL)
            {
                // invalid index
                return false;
            }

            List* pList = _out->getAs<types::List>();
            for (int i = 0; i < pList->getSize(); i++)
            {
                out.push_back(pList->get(i));
            }

            delete pList;
        }
        else if (arg->isString())
        {
            std::list<std::wstring> stFields;
            String * pString = arg->getAs<types::String>();
            for (int i = 0; i < pString->getSize(); ++i)
            {
                stFields.push_back(pString->get(i));
            }

            _out = extractStrings(stFields);
            if (_out == NULL)
            {
                // invalid index
                return false;
            }

            List* pList = _out->getAs<types::List>();
            for (int i = 0; i < pList->getSize(); i++)
            {
                out.push_back(pList->get(i));
            }

            delete pList;
        }
        else if (arg->isPoly())
        {
            Polynom* pPoly = arg->getAs<Polynom>();
            SinglePoly* pSinglePoly = pPoly->getFirst();

            int iMaxDim = 0;
            double dblParse = -1 * pSinglePoly->getFirst();
            int iSize = getSize();

            if (pSinglePoly->getRank() < 2 && dblParse >= 0 && dblParse < (double)iSize)
            {
                out.push_back(get(iSize - 1 - dblParse));
            }
            else
            {
                return false;
            }
        }

        if (out.empty() == false)
        {
            return true;
        }
    }
    Callable::ReturnValue ret;
    // Overload of extraction need
    // the tlist from where we extract
    this->IncreaseRef();
    in.push_back(this);

    std::wstring stType = getShortTypeStr();
    try
    {
        ret = Overload::call(L"%" + stType + L"_e", in, _iRetCount, out);
    }
    catch (const ast::InternalError &ie)
    {
        try
        {
            //to compatibility with scilab 5 code.
            //tlist/mlist name are truncated to 8 first character
            if (stType.size() > 8)
            {
                std::wcout << (L"%" + stType.substr(0, 8) + L"_e") << std::endl;
                ret = Overload::call(L"%" + stType.substr(0, 8) + L"_e", in, _iRetCount, out);
            }
            else
            {
                throw ie;
            }
        }
        catch (ast::InternalError & /*se*/)
        {
            ret = Overload::call(L"%l_e", in, _iRetCount, out);
        }
    }

    // Remove this from "in" for keep "in" unchanged.
    this->DecreaseRef();
    in.pop_back();

    if (ret == Callable::Error)
    {
        throw ast::InternalError(ConfigVariable::getLastErrorMessage(), ConfigVariable::getLastErrorNumber(), e.getLocation());
    }

    return true;
}

bool TList::extract(const std::wstring & name, InternalType *& out)
{
    int i = getFieldIndex(name);
    if (i != -1)
    {
        out = i < getSize() ? List::get(i) : NULL;
        return true;
    }

    return false;
}

InternalType* TList::getField(const std::wstring& _sKey)
{
    int i = getFieldIndex(_sKey);

    return (i < getSize()) ? List::get(i) : NULL;
}

int TList::getFieldIndex(const std::wstring& _sKey)
{
    if (getSize() < 1)
    {
        return -1;
    }

    String* pS = getFieldNames();
    int i = pS->getSize();
    // first field is the tlist type
    while (--i > 0)
    {
        if (wcscmp(pS->get(i), _sKey.c_str()) == 0)
        {
            return i;
        }
    }
    return -1;
}

InternalType* TList::extractStrings(const std::list<std::wstring>& _stFields)
{
    List* pLResult = new List();

    int* index = new int[_stFields.size()];

    int i = 0;
    std::list<std::wstring>::const_iterator it;
    for (it = _stFields.begin(); it != _stFields.end(); ++it, ++i)
    {
        index[i] = getFieldIndex(*it);

        if (index[i] == -1)
        {
            // non-existant field
            delete index;
            return pLResult;
        }
    }

    for (i = 0; i < _stFields.size(); ++i)
    {
        if (index[i] >= getSize())
        {
            // no corresponding field value
            delete index;
            delete pLResult;
            return NULL;
        }

        pLResult->set(i, List::get(index[i]));
    }

    delete index;
    return pLResult;
}

std::wstring TList::getTypeStr() const
{
    if (getSize() < 1)
    {
        return L"";
    }

    return getFieldNames()->getFirst();
}

std::wstring TList::getShortTypeStr() const
{
    return getTypeStr();
}

void TList::set(const std::wstring& _sKey, InternalType* _pIT)
{
    List::set(getFieldIndex(_sKey), _pIT);
}

void TList::set(const int _iIndex, InternalType* _pIT)
{
    List::set(_iIndex, _pIT);
}

String* TList::getFieldNames() const
{
    return (*m_plData)[0]->getAs<types::String>();
}

/**
** toString to display TLists
*/
bool TList::toString(std::wostringstream& ostr)
{
    //call overload %type_p if exists
    types::typed_list in;
    types::typed_list out;

    IncreaseRef();
    in.push_back(this);

    try
    {
        if (Overload::generateNameAndCall(L"p", in, 1, out) == Function::Error)
        {
            ConfigVariable::setError();
        }

        ostr.str(L"");
        DecreaseRef();
        return true;
    }
    catch (ast::InternalError& e)
    {
        if (e.GetErrorType() == ast::TYPE_ERROR)
        {
            DecreaseRef();
            throw e;
        }

        // avoid error message about undefined overload %type_p
        ConfigVariable::resetError();
    }

    DecreaseRef();

    // special case for lss
    if (getSize() != 0 &&
            (*m_plData)[0]->isString() &&
            (*m_plData)[0]->getAs<types::String>()->getSize() > 0 &&
            wcscmp((*m_plData)[0]->getAs<types::String>()->getFirst(), L"lss") == 0)
    {
        wchar_t* wcsVarName = os_wcsdup(ostr.str().c_str());
        int iPosition = 1;
        const wchar_t * wcsDesc[7] = {L"  (state-space system:)", L"= A matrix =", L"= B matrix =", L"= C matrix =", L"= D matrix =", L"= X0 (initial state) =", L"= Time domain ="};
        for (auto val : *m_plData)
        {
            std::wostringstream nextVarName;
            ostr.str(L"");
            nextVarName << " " << wcsVarName << L"(" << iPosition << L")";
            ostr << L"\n" << nextVarName.str() << wcsDesc[iPosition - 1] << L"\n\n";
            scilabWriteW(ostr.str().c_str());
            VariableToString(val, nextVarName.str().c_str());
            iPosition++;
        }
        ostr.str(L"");
        free(wcsVarName);
        return true;
    }

    // call normal toString
    return List::toString(ostr);
}
} // end namespace types
