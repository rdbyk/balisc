// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
// 02110-1301, USA.

#include "core_gw.hxx"
#include "function.hxx"
#include "context.hxx"
#include "string.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "sci_malloc.h"
}

using types::Function;
using types::String;
using types::typed_list;
using symbol::Context;
using symbol::Symbol;
using symbol::Variable;
using symbol::ScopedVariable;

static const char fname[] = "unprotect";

Function::ReturnValue sci_unprotect(typed_list &in, int _iRetCount, typed_list &out)
{
    Context *pCtx = Context::getInstance();

    if (in.size() == 0)
    {
        pCtx->unprotect();
        return Function::OK;
    }

    for (int i = 0; i < in.size(); ++i)
    {
        if (in[i]->isString() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: A String matrix expected.\n"), fname, i+1);
            return Function::Error;
        }
    }

    for (int i = 0; i < in.size(); ++i)
    {
        String* pS = in[i]->getAs<String>();
        
        for (int j = 0; j < pS->getSize(); ++j)
        {
            wchar_t* wcsVarName = pS->get(j);

            if (pCtx->isValidVariableName(wcsVarName) == false)
            {
                char* pstrVarName = wide_string_to_UTF8(wcsVarName);
                Scierror(999, _("%s: Wrong value \"%s\" in argument #%d: A valid variable name expected.\n"), fname, pstrVarName, i+1);
                FREE(pstrVarName);
                return Function::Error;
            }

            if (pCtx->get(Symbol(wcsVarName)) == NULL)
            {
                char* pstrVarName = wide_string_to_UTF8(wcsVarName);
                Scierror(999, _("%s: Wrong value \"%s\" in argument #%d: An existent variable expected.\n"), fname, pstrVarName, i+1);
                FREE(pstrVarName);
                return Function::Error;
            }
        }

        for (int j = 0; j < pS->getSize(); ++j)
        {
            wchar_t* wcsVarName = pS->get(j);

            Variable* pV = pCtx->getOrCreate(Symbol(wcsVarName));

            if (pV->empty() == false)
            {
                ScopedVariable* pSV = pV->top();
                pSV->protect = false;
            }
        }
    }

    return Function::OK;
}
