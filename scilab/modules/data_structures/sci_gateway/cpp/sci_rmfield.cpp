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


#include "data_structures_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "struct.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Function;
using types::String;
using types::Struct;
using types::typed_list;

static const char fname[] = "rmfield";

Function::ReturnValue sci_rmfield(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 2)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d expected.\n"), fname, 2);
        return Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d : A matrix of strings expected.\n"), fname, 1);
        return Function::Error;
    }
    
    if (in[1]->isStruct() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d : Struct expected.\n"), fname, 2);
        return Function::Error;
    }

    
    String* f = in[0]->getAs<String>();
    Struct* s = in[1]->getAs<Struct>();
    
    for (int i = 0; i < f->getSize(); ++i)
    { 
        s->removeField(f->get(i));
    }

    out.push_back(s);

    return Function::OK;
}
