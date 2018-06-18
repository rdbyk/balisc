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
}

using types::Bool;
using types::Double;
using types::Function;
using types::String;
using types::typed_list;
using symbol::Context;
using symbol::Symbol;

static const char fname[] = "isprotected";

Function::ReturnValue sci_isprotected(typed_list &in, int _iRetCount, typed_list &out)
{
    Context *pCtx = Context::getInstance();

    if (in.size() == 0)
    {
        std::list<std::wstring> pvars;

        int n = pCtx->protectedVars(pvars);

        if (n == 0)
        {
            // return []
            out.push_back(types::Double::Empty());
            return Function::OK;
        }

        String* pS = new types::String(n, 1);

        int i = 0;
        for (auto p : pvars)
        {
            pS->set(i++, p.c_str());
        }

        out.push_back(pS);
        return Function::OK;
    }

    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d to %d expected.\n"), fname, 0, 1);
        return types::Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A String expected.\n"), fname, 1);
        return types::Function::Error;
    }
    
    String* pS = in[0]->getAs<String>();

    for (int i = 0; i < pS->getSize(); ++i)
    {
        wchar_t* wcsVarName = pS->get(i);

        if (pCtx->isValidVariableName(wcsVarName) == false)
        {
            char* pstrVarName = wide_string_to_UTF8(wcsVarName);
            Scierror(999, _("%s: Wrong value \"%s\" in argument #%d: A valid variable name expected.\n"), fname, pstrVarName, 1);
            FREE(pstrVarName);
            return Function::Error;
        }
    }

    Bool* pB = new Bool(pS->getDims(), pS->getDimsArray());
    int* pb = pB->get();

    for (int i = 0; i < pS->getSize(); ++i)
    {
        pb[i] = pCtx->isprotected(Symbol(pS->get(i)));
    }
    
    out.push_back(pB);
    return Function::OK;
}
