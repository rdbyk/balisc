/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2013 - Scilab Enterprises - Cedric Delamarre
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

#include "core_gw.hxx"
#include "function.hxx"
#include "context.hxx"
#include "string.hxx"
#include "bool.hxx"
#include "double.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
}

using symbol::Context;
using symbol::Symbol;
using types::Bool;
using types::Double;
using types::Function;
using types::String;
using types::typed_list;

#define FNAME_EXISTS 0
#define FNAME_ISDEF  1

static const char* fname[] = {"exists", "isdef"};

template <typename T, typename U, int W>
Function::ReturnValue exists(typed_list &in, int _iRetCount, typed_list &out)
{
    String* pStrIn = NULL;

    if (in.size() != 1 && in.size() != 2)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d to %d expected."), fname[W], 1, 2);
        return Function::Error;
    }

    if (!in[0]->isString())
    {
        Scierror(999, _("%s: Wrong type for argument #%d: Matrix of strings expected.\n"), fname[W], 1);
        return Function::Error;
    }

    if (in.size() == 2 && (!in[1]->isString() || in[1]->getAs<String>()->getSize() != 1))
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A single string expected.\n"), fname[W], 2);
        return Function::Error;
    }

    pStrIn  = in[0]->getAs<String>();

    T* pOut = new T(pStrIn->getDims(), pStrIn->getDimsArray());
    U* p = pOut->get();
    Context* ctx = Context::getInstance();

    if (in.size() == 2)
    {
        const wchar_t* psScope = in[1]->getAs<String>()->getFirst();

        if (wcscmp(psScope, L"all") == 0 || wcscmp(psScope, L"a") == 0)
        {
            for (int i = 0; i < pStrIn->getSize(); i++)
            {
                p[i] = ctx->get(Symbol(pStrIn->get(i))) != NULL;
            }
        }
        else if (wcscmp(psScope, L"local") == 0 || wcscmp(psScope, L"l") == 0)
        {
            for (int i = 0; i < pStrIn->getSize(); i++)
            {
                p[i] = ctx->getCurrentLevel(Symbol(pStrIn->get(i))) != NULL;
            }
        }
        else if (wcscmp(psScope, L"nolocal") == 0 || wcscmp(psScope, L"n") == 0)
        {
            for (int i = 0; i < pStrIn->getSize(); i++)
            {
                p[i] = ctx->getAllButCurrentLevel(Symbol(pStrIn->get(i))) != NULL;
            }
        }
        else
        {
            Scierror(110, _("\'a\', \'l\', or \'n\'"));
            delete pOut;
            return Function::Error;
        }
    }
    else
    {
        // default is "All"
        for (int i = 0; i < pStrIn->getSize(); i++)
        {
            p[i] = ctx->get(Symbol(pStrIn->get(i))) != NULL;
        }
    }

    out.push_back(pOut);
    return Function::OK;
}

Function::ReturnValue sci_exists(typed_list &in, int _iRetCount, typed_list &out)
{
    return exists<Double, double, FNAME_EXISTS>(in, _iRetCount, out);
}

Function::ReturnValue sci_isdef(typed_list &in, int _iRetCount, typed_list &out)
{
    return exists<Bool, int, FNAME_ISDEF>(in, _iRetCount, out);
}
