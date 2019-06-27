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
#include "int.hxx"
#include "double.hxx"
#include "string.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "sci_malloc.h"
}

using types::Double;
using types::Function;
using types::GenericType;
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

static std::map<std::wstring, InternalType::ScilabType> str_to_type = {
    { L"int8", InternalType::ScilabInt8 },
    { L"int16", InternalType::ScilabInt16 },
    { L"int32", InternalType::ScilabInt32 },
    { L"int64", InternalType::ScilabInt64 },
    { L"uint8", InternalType::ScilabUInt8 },
    { L"uint16", InternalType::ScilabUInt16 },
    { L"uint32", InternalType::ScilabUInt32 },
    { L"uint64", InternalType::ScilabUInt64 },
    { L"double", InternalType::ScilabDouble }
};

static int digit_value(wchar_t d);

template<typename T> 
T* matrix_base_n_to_dec(String* str, int base)
{
    T* dec = new T(str->getDims(), str->getDimsArray());
    auto d = dec->get();

    for (int i = 0; i < str->getSize(); ++i)
    {
        wchar_t* s = str->get(i);
        int v = digit_value(s[0]);
        
        // invalid digit?
        if (v >= base || v < 0)
        {
            delete dec;
            Scierror(110, 1, _("valid characters for chosen 'base' representation"));
            return NULL;
        }

        d[i] = v;

        for(int j = 1; s[j]; ++j)
        {
            v = digit_value(s[j]);

            // invalid digit?
            if (v >= base || v < 0)
            {
                delete dec;
                Scierror(110, 1, _("valid characters for chosen 'base' representation"));
                return NULL;
            }
            d[i] *= base;
            d[i] += v;
        }
    }
    
    return dec;
}

template<> 
Double* matrix_base_n_to_dec(String* str, int base)
{
    Double* dec = new Double(str->getDims(), str->getDimsArray());
    auto d = dec->get();

    for (int i = 0; i < str->getSize(); ++i)
    {
        wchar_t* s = str->get(i);
        int v = digit_value(s[0]);
        
        // invalid digit?
        if (v >= base || v < 0)
        {
            d[i] = NAN;
            continue;
        }

        d[i] = v;

        for(int j = 1; s[j]; ++j)
        {
            v = digit_value(s[j]);

            // invalid digit?
            if (v >= base || v < 0)
            {
                d[i] = NAN;
                break;
            }
            d[i] *= base;
            d[i] += v;
        }
    }
    
    return dec;
}

Function::ReturnValue sci_base2dec(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() < 2 || in.size() > 3)
    {
        Scierror(72, 2, 3);
        return Function::Error;
    }

    int base = 2;

    if (in.size() >= 2)
    {
        if (in[0]->isString() == false 
            && in[0]->isDouble() == false && in[0]->getAs<Double>()->isEmpty() == false)
        {
            Scierror(91, 1);
            return Function::Error;
        }
        
        if (in[1]->isDouble() == false && in[1]->getAs<Double>()->isScalar() == false)
        {
            Scierror(93, 2);
            return Function::Error;
        }
        
        base = static_cast<int>(in[1]->getAs<Double>()->getFirst());
        
        if (in[1]->getAs<Double>()->getFirst() != base || base < 2 || base > 36)
        {
            Scierror(110, 2, _("integer value from 2 to 36"));
            return Function::Error;
        }
    }

    InternalType::ScilabType res_type = InternalType::ScilabDouble;

    if (in.size() == 3)
    {
        if (in[2]->isString() == false || in[2]->getAs<String>()->isScalar() == false)
        {
            Scierror(102, 3);
            return Function::Error;
        }
        
        auto found = str_to_type.find(in[2]->getAs<String>()->getFirst());

        if (found == str_to_type.end())
        {
            Scierror(110, 3, _("'int8',..,'int64','uint8',..,'uint64', or 'double'"));
            return Function::Error;
        }
        
        res_type = found->second;
    }

    if (in[0]->getAs<GenericType>()->getSize() == 0)
    {
        out.push_back(Double::Empty());
        return Function::OK;
    }

    String* str = in[0]->getAs<String>();
    InternalType* result = NULL;

    switch(res_type)
    {
        case InternalType::ScilabInt8:
            result = matrix_base_n_to_dec<Int8>(str, base);
            break;
        case InternalType::ScilabInt16:
            result = matrix_base_n_to_dec<Int16>(str, base);
            break;
        case InternalType::ScilabInt32:
            result = matrix_base_n_to_dec<Int32>(str, base);
            break;
        case InternalType::ScilabInt64:
            result = matrix_base_n_to_dec<Int64>(str, base);
            break;
        case InternalType::ScilabUInt8:
            result = matrix_base_n_to_dec<UInt8>(str, base);
            break;
        case InternalType::ScilabUInt16:
            result = matrix_base_n_to_dec<UInt16>(str, base);
            break;
        case InternalType::ScilabUInt32:
            result = matrix_base_n_to_dec<UInt32>(str, base);
            break;
        case InternalType::ScilabUInt64:
            result = matrix_base_n_to_dec<UInt64>(str, base);
            break;
        case InternalType::ScilabDouble:
            result = matrix_base_n_to_dec<Double>(str, base);
            break;
        default:
            // unknown error
            Scierror(0);
            return Function::Error;
    }

    if (result)
    {
        out.push_back(result);
        return Function::OK;
    }
    else
    {
        // Scierror was set in 'matrix_base_n_to_dec'
        return Function::Error;
    }
}

// a digit value "v=digit_value(d)" should be checked as follows:
//   "v < base && v >=0" => digit is valid
//   otherwise           => digit is invalid
static int digit_value(wchar_t d)
{
    if (d <= L'9')
    {
        return d - L'0';   
    }
    else if (d >= L'A' && d <= L'Z')
    {
        return d - L'7';
    }
    else if (d >= L'a')
    {
        return d - L'W';
    }
    else
    {
        return -1; // invalid
    }
}
