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

#include "elem_func_gw.hxx"
#include "function.hxx"
#include "types.hxx"
#include "internal.hxx"
#include "arrayof.hxx"
#include "overload.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::ArrayOf;
using types::Bool;
using types::Function;
using types::GenericType;
using types::InternalType;
using types::typed_list;

Function::ReturnValue sci_isvector(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71, 1);
        return Function::Error;
    }

    switch (in[0]->getType())
    {
        case InternalType::ScilabMList:
        case InternalType::ScilabTList:
        case InternalType::ScilabUserType:
        {
            std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_isvector";
            return Overload::call(wstFuncName, in, _iRetCount, out);
            break;
        }
        default:
        {
            if (in[0]->isArrayOf())
            {
                GenericType* g = in[0]->getAs<GenericType>();
                out.push_back(new Bool(g->isVector() && g->getSize() > 1));
            }
            else
            {
                out.push_back(Bool::False());
            }
            return Function::OK;
            break;
        }
    }
}
