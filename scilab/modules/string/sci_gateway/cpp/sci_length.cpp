/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA 2007 - Cong WU
 * Copyright (C) INRIA 2008 - Allan CORNET
 * Copyright (C) DIGITEO 2009 - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "function.hxx"
#include "string.hxx"
#include "mlist.hxx"
#include "double.hxx"
#include "internal.hxx"
#include "string_gw.hxx"
#include "context.hxx"
#include "overload.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
}

using types::Double;
using types::Function;
using types::GenericType;
using types::InternalType;
using types::List;
using types::MList;
using types::String;
using types::typed_list;

static Double* lengthStrings(String* _pS);

Function::ReturnValue sci_length(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71, 1);
        return Function::Error;
    }

    InternalType* in0 = in[0];

    if (in0->isString())
    {
        out.push_back(lengthStrings(in0->getAs<String>()));
        return Function::OK;
    }
    else if (in0->isList())
    {
        if (in0->isMList())
        {
            MList* pML = in0->getAs<MList>();
            std::wstring wstFuncName = L"%" + pML->getShortTypeStr() + L"_length";
            symbol::Context* pCtx = symbol::Context::getInstance();
            InternalType* pFunc = pCtx->get(symbol::Symbol(wstFuncName));

            if (pFunc && pFunc->isCallable())
            {
                Overload::call(wstFuncName, in, _iRetCount, out);
                return Function::OK;
            }
        }

        out.push_back(new Double(static_cast<double>(in0->getAs<List>()->getSize())));
        return Function::OK;
    }
    else if (in0->isGenericType())
    {
        out.push_back(new Double(static_cast<double>(in0->getAs<GenericType>()->getSize())));
        return Function::OK;
    }
    else
    {
        Scierror(90, 1, _("array, container, library, or user type"));
        return Function::Error;
    }
}

Double* lengthStrings(String* _pS)
{
    Double* pD = new Double(_pS->getDims(), _pS->getDimsArray());
    wchar_t** pwst = _pS->get();
    double* pdbl = pD->get();

    for (int i = 0 ; i < _pS->getSize() ; i++)
    {
        pdbl[i] = static_cast<double>(wcslen(pwst[i]));
    }

    return pD;
}
