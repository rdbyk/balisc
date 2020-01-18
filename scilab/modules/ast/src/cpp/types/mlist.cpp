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

#include "mlist.hxx"
#include "callable.hxx"
#include "configvariable.hxx"
#include "context.hxx"
#include "exp.hxx"
#include "overload.hxx"
#include "types_tools.hxx"
#include <sstream>

#ifndef NDEBUG
#include "inspector.hxx"
#endif

extern "C"
{
#include "sci_malloc.h"
#include "sciprint.h"
}

namespace types
{

MList::~MList()
{
    typed_list in;
    typed_list out;
    optional_list opt;
    IncreaseRef();
    in.push_back(this);

    std::wstring stFunc = Overload::buildOverloadName(L"clear", in, 0);
    InternalType *pIT = symbol::Context::getInstance()->get(symbol::Symbol(stFunc));

    if (pIT && pIT->isCallable())
    {
        bool bError = false;

        try
        {
            if (Overload::call(stFunc, in, 0, out) == Callable::Error)
            {
                bError = true;
            }
        }
        catch (const ast::InternalError& ie)
        {
            bError = true;
        }
        catch (const ast::RecursionException& re)
        {
            bError = true;
        }

        if (bError)
        {
            // FIXME: provide more detailed info about error
            if (ConfigVariable::getWarningMode())
            {
                char* pstFuncName = wide_string_to_UTF8(stFunc.c_str());
                sciprint("WARNING: error in %s.\n", pstFuncName);
                FREE(pstFuncName);
            }

            ConfigVariable::resetError();
            ConfigVariable::resetWhereError();
        }
    }

    DecreaseRef();
}

bool MList::getMemory(int* _piSize, int* _piSizePlusType)
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

    *_piSizePlusType += sizeof(MList);
    return true;
}

bool MList::invoke(typed_list & in, optional_list & /*opt*/, int _iRetCount, typed_list & out, const ast::Exp & e)
{
    if (in.size() == 0)
    {
        out.push_back(this);
        return true;
    }
    else if (in.size() == 1)
    {
        InternalType * arg = in[0];
        InternalType* _out = NULL;
        if (arg->isString())
        {
            std::list<std::wstring> stFields;
            String * pString = arg->getAs<types::String>();
            for (int i = 0; i < pString->getSize(); ++i)
            {
                stFields.push_back(pString->get(i));
            }

            _out = extractStrings(stFields);

            if (_out)
            {
                List* pList = _out->getAs<types::List>();
                for (int i = 0; i < pList->getSize(); i++)
                {
                    out.push_back(pList->get(i));
                }
                delete pList;
            }
        }

        if (!out.empty())
        {
            return true;
        }
    }

    Callable::ReturnValue ret;
    // Overload of extraction need
    // the mlist from where we extract
    this->IncreaseRef();
    in.push_back(this);

    try
    {
        ret = Overload::call(L"%" + getShortTypeStr() + L"_e", in, _iRetCount, out);
    }
    catch (ast::InternalError & /*se*/)
    {
        if (ConfigVariable::getLastErrorFunction().empty())
        {
            ret = Overload::call(L"%l_e", in, _iRetCount, out);
        }
        else
        {
            throw;
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
}
