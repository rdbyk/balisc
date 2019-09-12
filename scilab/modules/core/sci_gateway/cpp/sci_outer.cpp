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
#include "variables.hxx"
#include "string.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "sci_malloc.h"
}

using types::Function;
using types::InternalType;
using types::String;
using types::typed_list;
using symbol::Context;
using symbol::Symbol;

Function::ReturnValue sci_outer(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() == 0)
    {
        Scierror(74, 1);
        return Function::Error;
    }

    for (int i = 0; i < in.size(); ++i)
    {
        if (in[i]->isString() == false)
        {
            Scierror(91,  i+1);
            return Function::Error;
        }
    }

    Context *ctx = Context::getInstance();

    for (int i = 0; i < in.size(); ++i)
    {
        String* pS = in[i]->getAs<String>();
        
        for (int j = 0; j < pS->getSize(); ++j)
        {
            wchar_t* wname = pS->get(j);
            Symbol sym = Symbol(wname);
            
            if (InternalType* value = ctx->getCurrentLevel(sym))
            {
                ctx->putInPreviousScope(ctx->getOrCreate(sym), value);
            }
            else
            {
                char* name = wide_string_to_UTF8(wname);
                Scierror(40, name);
                FREE(name);
                return Function::Error;
            }
        }
    }

    return Function::OK;
}
