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
#include "bool.hxx"
#include "int.hxx"
#include "double.hxx"
#include "string.hxx"

#include <float.h>

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Function;
using types::Int8;
using types::Int16;
using types::Int32;
using types::Int64;
using types::InternalType;
using types::String;
using types::typed_list;
using types::UInt8;
using types::UInt16;
using types::UInt32;
using types::UInt64;

static std::map<std::wstring, std::pair<InternalType::ScilabType, unsigned long long>> int_max = {
    { L"int8", { InternalType::ScilabInt8, SCHAR_MAX } },
    { L"int16", { InternalType::ScilabInt16, SHRT_MAX } },
    { L"int32", { InternalType::ScilabInt32,  INT_MAX} },
    { L"int64", { InternalType::ScilabInt64,  LONG_MAX} },
    { L"uint8", { InternalType::ScilabUInt8, UCHAR_MAX } },
    { L"uint16", { InternalType::ScilabUInt16, USHRT_MAX } },
    { L"uint32", { InternalType::ScilabUInt32, UINT_MAX } },
    { L"uint64", { InternalType::ScilabUInt64, ULONG_MAX } }
};

Function::ReturnValue sci_intmax(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() > 1)
    {
        Scierror(72, 0, 1);
        return Function::Error;
    }

    std::wstring in_typestr = L"int32";

    if (in.size() == 1)
    {
        if (in[0]->isString())
        {
            if (in[0]->getAs<String>()->isScalar())
            {
                in_typestr = in[0]->getAs<String>()->getFirst();
            }
            else
            {
                Scierror(102, 1);
                return Function::Error;
            }
        }
        else
        {
            if (in[0]->isInt())
            {
                in_typestr = in[0]->getTypeStr();
            }
            else
            {
                Scierror(90, 1, _("integer or string"));
                return Function::Error;
            }
        }
    }
    
    auto found = int_max.find(in_typestr);
    
    if (found == int_max.end())
    {
        if (in[0]->isString())
        {
            Scierror(110, 1, _("'int8',..,'int64','uint8',..,'uint64'"));
        }
        else
        {
            Scierror(92, 1);
        }
        return Function::Error;
    }

    InternalType::ScilabType out_type = found->second.first;
    auto out_value = found->second.second;
    
    InternalType* result = NULL;

    switch(out_type)
    {
        case InternalType::ScilabInt8:
            result = new Int8(out_value);
            break;
        case InternalType::ScilabInt16:
            result = new Int16(out_value);
            break;
        case InternalType::ScilabInt32:
            result = new Int32(out_value);
            break;
        case InternalType::ScilabInt64:
            result = new Int64(out_value);
            break;
        case InternalType::ScilabUInt8:
            result = new UInt8(out_value);
            break;
        case InternalType::ScilabUInt16:
            result = new UInt16(out_value);
            break;
        case InternalType::ScilabUInt32:
            result = new UInt32(out_value);
            break;
        case InternalType::ScilabUInt64:
            result = new UInt64(out_value);
            break;
        
        default:
            // unknown error
            Scierror(0);
            return Function::Error;
    }

    out.push_back(result);
    return Function::OK;
}
