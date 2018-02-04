/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Antoine ELIAS
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
#include "context.hxx"
#include "double.hxx"
#include "string.hxx"
#include "core_gw.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
}

using types::Double;
using types::Function;
using types::InternalType;
using types::String;
using types::typed_list;
using symbol::Context;
using symbol::Symbol;

static const char fname[] = "global";

Function::ReturnValue sci_global(typed_list &in, int _iRetCount, typed_list &out)
{
    Context* pCtx = Context::getInstance();

    for (int i = 0 ; i < in.size() ; i++)
    {
        if (in[i]->isString() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: String expected.\n"), fname, i + 1);
            return Function::Error;
        }

        if (in[i]->getAs<String>()->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), fname, i + 1);
            return Function::Error;
        }

        wchar_t* wcsVarName = in[i]->getAs<String>()->getFirst();

        if (pCtx->isValidVariableName(wcsVarName) == false)
        {
            char* pstrVarName = wide_string_to_UTF8(wcsVarName);
            Scierror(999, _("%s: Wrong value for argument #%d: %s\n"), fname, i + 1, pstrVarName);
            FREE(pstrVarName);
            return Function::Error;
        }

        if (pCtx->isprotected(Symbol(wcsVarName)))
        {
            Scierror(999, _("%s: Redefining permanent variable.\n"), fname);
            return Function::Error;
        }
    }

    if (_iRetCount > 1)
    {
        Scierror(999, _("%s: Wrong number of output arguments: At most %d expected.\n"), fname, 1);
        return Function::Error;
    }

    for (int i = 0 ; i < in.size() ; i++)
    {
        wchar_t* wcsVarName = in[i]->getAs<String>()->getFirst();

        Symbol pstVar(Symbol(const_cast<wchar_t*>(wcsVarName)));

        if (pCtx->isGlobalVisible(pstVar))
        {
            continue;
        }

        InternalType* pIT = NULL;

        if (pCtx->isGlobal(pstVar))
        {
            pIT = pCtx->getGlobalValue(pstVar);
        }
        else
        {
            pIT = pCtx->get(pstVar);
            pCtx->setGlobal(pstVar);
        }

        // set global variable visible in current scope
        pCtx->setGlobalVisible(pstVar, true);

        if (pIT)
        {
            // assign local value to new global variable
            pCtx->put(pstVar, pIT);
        }
        else
        {
            pCtx->put(pstVar, Double::Empty());
        }

    }

    return Function::OK;
}
