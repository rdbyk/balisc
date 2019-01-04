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
#include "listinsert.hxx"
#include "listundefined.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Function;
using types::ListInsert;
using types::ListUndefined;
using types::typed_list;

Function::ReturnValue sci_insert(typed_list &in, int _iRetCount, typed_list &out)
{
    switch(in.size())
    {
        case 0:
            out.push_back(new ListInsert(new ListUndefined()));
            break;

        case 1:
            out.push_back(new ListInsert(in[0]));
            break;

        default:
            Scierror(72, 0, 1);
            return Function::Error;
    }

    return Function::OK;
}
