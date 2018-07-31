/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
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

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Function;
using types::String;
using types::typed_list;
using symbol::Context;
using symbol::Symbol;

static const char fname[] = "clearglobal";

Function::ReturnValue sci_clearglobal(typed_list &in, int _iRetCount, typed_list &out)
{
    Context *pCtx = Context::getInstance();

    if (in.size() == 0)
    {
        std::list<std::pair<std::wstring,int>> gVars;

        pCtx->getGlobalInfoForWho(gVars, false);

        for (auto g : gVars)
        {
            if (pCtx->isprotected(Symbol(g.first)))
            {
                Scierror(999, _("%s: Redefining permanent variable.\n"), fname);
                return Function::Error;
            }
        }

        for (auto g : gVars)
        {
            pCtx->removeGlobal(Symbol(g.first));
        }
    }
    else
    {
        for (int i = 0; i < in.size(); ++i)
        {
            if (in[i]->isString() == false || in[i]->getAs<String>()->getSize() != 1)
            {
                Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), fname, i + 1);
                return Function::Error;
            }

            wchar_t* wcsVarName = in[i]->getAs<String>()->getFirst();

            if (pCtx->isprotected(Symbol(wcsVarName)))
            {
                Scierror(999, _("%s: Redefining permanent variable.\n"), fname);
                return Function::Error;
            }
        }

        for (int i = 0; i < in.size(); ++i)
        {
            pCtx->removeGlobal(Symbol(in[i]->getAs<String>()->getFirst()));
        }
    }
    return Function::OK;
}
