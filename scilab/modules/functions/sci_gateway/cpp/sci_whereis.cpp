/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2019 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "functions_gw.hxx"
#include "context.hxx"
#include "string.hxx"
#include "double.hxx"

extern "C" {
#include "Scierror.h"
#include "localization.h"
}

types::Function::ReturnValue sci_whereis(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71, 1);
        return types::Function::Error;
    }

    if (in[0]->isString())
    {
        types::String* pS = in[0]->getAs<types::String>();

        if (pS->isScalar() == false)
        {
            Scierror(91, 1);
            return types::Function::Error;
        }

        std::wstring sym(pS->get()[0]);
        types::InternalType* pIT = symbol::Context::getInstance()->get(symbol::Symbol(sym));
        if (pIT)
        {
            switch (pIT->getType())
            {
                case types::InternalType::ScilabFunction:
                    out.push_back(new types::String(pIT->getAs<types::Callable>()->getModule().c_str()));
                    return types::Function::OK;
                case types::InternalType::ScilabMacro:
                    out.push_back(new types::String(pIT->getAs<types::Callable>()->getModule().c_str()));
                    break;
                default:
                    break;
            }
        }

        std::list<std::wstring> lst;
        int size = symbol::Context::getInstance()->getWhereIs(lst, pS->get()[0]);
        if (lst.empty())
        {
            if (out.empty())
            {
                out.push_back(types::Double::Empty());
            }
            return types::Function::OK;
        }

        types::String* pOut = new types::String(size, 1);
        int i = 0;
        for (std::wstring l : lst)
        {
            pOut->set(i++, l.c_str());
        }

        out.push_back(pOut);
    }
    else
    {
        switch (in[0]->getType())
        {
            case types::InternalType::ScilabFunction:
            case types::InternalType::ScilabMacro:
            case types::InternalType::ScilabMacroFile:
                out.push_back(new types::String(in[0]->getAs<types::Callable>()->getModule().c_str()));
                break;
            default:
                out.push_back(types::Double::Empty());
        }
    }

    return types::Function::OK;
}
