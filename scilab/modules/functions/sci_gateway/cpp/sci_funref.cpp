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

#include "functions_gw.hxx"
#include "double.hxx"
#include "string.hxx"
#include "context.hxx"
#include "callable.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Callable;
using types::Double;
using types::Function;
using types::InternalType;
using types::MacroFile;
using types::String;
using types::typed_list;

using symbol::Context;
using symbol::Symbol;

types::Function::ReturnValue sci_funref(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71 , 1);
        return Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(91 , 1);
        return Function::Error;
    }

    String *pS = in[0]->getAs<String>();

    if (pS->getSize() != 1)
    {
        Scierror(102 , 1);
        return Function::Error;
    }

    InternalType *pIT = Context::getInstance()->get(Symbol(pS->getFirst()));

    if (pIT && pIT->isCallable())
    {
        out.push_back(pIT->getAs<types::Callable>());
    }
    else
    {
        out.push_back(Double::Empty());
    }
    
    return Function::OK;
}
