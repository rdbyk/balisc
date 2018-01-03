// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
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

#include "graphics_gw.hxx"
#include "function.hxx"
#include "string.hxx"

extern "C"
{
#include "Scierror.h"
#include "GetHashTable.h"
}

using types::Function;
using types::InternalType;

Function::ReturnValue sci_gca(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 0)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), "gca", 0);
        return Function::Error;
    }
    
    InternalType* res = static_cast<InternalType*>(callGetProperty(NULL, 0, "current_axes"));

    if (res)
    {
        out.push_back(res);
        return Function::OK;
    }
    else
    {
        return Function::Error;
    }
}
