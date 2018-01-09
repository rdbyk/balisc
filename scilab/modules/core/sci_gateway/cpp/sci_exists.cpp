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
#include "strcmp.h"
}

enum ScopeRange
{
    Local,
    NoLocal,
    All,
    UnknownRange
};

static ScopeRange getScopeFromOption(const wchar_t *_psScope)
{
    if (wcscmp(_psScope, L"all") == 0 || wcscmp(_psScope, L"a") == 0)
    {
        return All;
    }
    if (wcscmp(_psScope, L"local") == 0 || wcscmp(_psScope, L"l") == 0)
    {
        return Local;
    }
    if (wcscmp(_psScope, L"nolocal") == 0 || wcscmp(_psScope, L"n") == 0)
    {
        return NoLocal;
    }

    return UnknownRange;
}

#define FNAME_EXISTS 0
#define FNAME_ISDEF  1

static const char* fname[] = {"exists", "isdef"};

template <typename T, typename U, int W>
types::Function::ReturnValue exists(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::String* pStrIn = NULL;

    if (in.size() != 1 && in.size() != 2)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d to %d expected."), fname[W], 1, 2);
        return types::Function::Error;
    }

    if (!in[0]->isString())
    {
        Scierror(999, _("%s: Wrong type for argument #%d: Matrix of strings expected.\n"), fname[W], 1);
        return types::Function::Error;
    }

    if (in.size() == 2 && (!in[1]->isString() || in[1]->getAs<types::String>()->getSize() != 1))
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A single string expected.\n"), fname[W], 2);
        return types::Function::Error;
    }

    const wchar_t *psScope = L"all"; // Default option is "all"
    if (in.size() == 2)
    {
        psScope = in[1]->getAs<types::String>()->getFirst();
    }

    pStrIn  = in[0]->getAs<types::String>();

    T* pOut = new T(pStrIn->getDims(), pStrIn->getDimsArray());
    U* p = pOut->get();
    symbol::Context* ctx = symbol::Context::getInstance();

    switch (getScopeFromOption(psScope))
    {
        case All:
            for (int i = 0; i < pStrIn->getSize(); i++)
            {
                p[i] = ctx->get(symbol::Symbol(pStrIn->get(i))) != NULL;
            }
            break;
        case Local:
            for (int i = 0; i < pStrIn->getSize(); i++)
            {
                p[i] = ctx->getCurrentLevel(symbol::Symbol(pStrIn->get(i))) != NULL;
            }
            break;
        case NoLocal:
            for (int i = 0; i < pStrIn->getSize(); i++)
            {
                p[i] = ctx->getAllButCurrentLevel(symbol::Symbol(pStrIn->get(i))) != NULL;
            }
            break;
        default :
            Scierror(36, _("%s: Wrong input argument %d.\n"), fname[W], 2);
            return types::Function::Error;
    }

    out.push_back(pOut);
    return types::Function::OK;
}

types::Function::ReturnValue sci_exists(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    return exists<types::Double, double, FNAME_EXISTS>(in, _iRetCount, out);
}

types::Function::ReturnValue sci_isdef(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    return exists<types::Bool, int, FNAME_ISDEF>(in, _iRetCount, out);
}
