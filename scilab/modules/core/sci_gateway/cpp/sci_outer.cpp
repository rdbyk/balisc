// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
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
    if (in.size() < 1 || in.size() > 2)
    {
        Scierror(72, 1, 2);
        return Function::Error;
    }

    if (in[0]->isString() == false || in[0]->getAs<String>()->isScalar() == false)
    {
        Scierror(91, 1);
        return Function::Error;
    }

    Context *ctx = Context::getInstance();

    if (ctx->getScopeLevel() < 2)
    {
        Scierror(61);
        return Function::Error;
    }

    wchar_t* name = in[0]->getAs<String>()->getFirst();
    Symbol symbol = Symbol(name);
    InternalType* value = (in.size() == 2) ? in[1] : ctx->getCurrentLevel(symbol);

    if (value)
    {
        ctx->putInPreviousScope(ctx->getOrCreate(symbol), value);
        return Function::OK;
    }
    else
    {
        char* v = wide_string_to_UTF8(name);
        Scierror(40, v);
        FREE(v);
        return Function::Error;
    }
}
