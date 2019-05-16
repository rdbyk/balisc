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

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Bool;
using types::Double;
using types::GenericType;
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

static std::map<std::wstring, std::pair<InternalType::ScilabType,int>> to_types = {
    { L"bool", { InternalType::ScilabBool, sizeof(int) * CHAR_BIT } },
    { L"int8", { InternalType::ScilabInt8, sizeof(char) * CHAR_BIT } },
    { L"int16", { InternalType::ScilabInt16, sizeof(short int) * CHAR_BIT } },
    { L"int32", { InternalType::ScilabInt32, sizeof(int) * CHAR_BIT } },
    { L"int64", { InternalType::ScilabInt64, sizeof(long long int) * CHAR_BIT } },
    { L"uint8", { InternalType::ScilabUInt8, sizeof(unsigned char) * CHAR_BIT } },
    { L"uint16", { InternalType::ScilabUInt16, sizeof(short unsigned int) * CHAR_BIT } },
    { L"uint32", { InternalType::ScilabUInt32, sizeof(unsigned int) * CHAR_BIT } },
    { L"uint64", { InternalType::ScilabUInt64, sizeof(long long unsigned int) * CHAR_BIT } },
    { L"double", { InternalType::ScilabDouble, sizeof(double) * CHAR_BIT } }
};

static int bytes_of_data(InternalType* in);

Function::ReturnValue sci_typecast(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 2)
    {
        Scierror(71, 2);
        return Function::Error;
    }
    
    if (!in[0]->isBool() && !in[0]->isInt() &&
        !(in[0]->isDouble() && !in[0]->getAs<Double>()->isComplex()))
    {
        Scierror(90, 1, _("real, integer, or boolean"));
        return Function::Error;
    }
    
    if (in[0]->getAs<GenericType>()->isIdentity())
    {
        Scierror(100, 1, _("fixed size argument"));
        return Function::Error;
    }

    if (in[1]->isString() == false)
    {
        Scierror(91, 2);
        return Function::Error;
    }
    
    if (in[1]->getAs<String>()->isScalar() == false)
    {
        Scierror(102, 2);
        return Function::Error;
    }
    
    auto found = to_types.find(in[1]->getAs<String>()->getFirst());
    
    if (found == to_types.end())
    {
        Scierror(110, 2, _("'bool','int8',..,'int64','uint8',..,'uint64', or 'double'"));
        return Function::Error;
    }

    if (in[0]->isDouble() && in[0]->getAs<Double>()->isEmpty())
    {
        out.push_back(Double::Empty());
        return Function::OK;
    }

    // calculate and check size of output
    int out_bits_per_element = found->second.second;
    int in_bytes = bytes_of_data(in[0]);
    size_t in_bits = ((size_t)CHAR_BIT) * in_bytes;

    if (in_bits % out_bits_per_element)
    {
        Scierror(110, 1, _("bit length divisable by that of cast type"));
        return Function::Error;
    }

    size_t out_size = in_bits / out_bits_per_element;

    if (out_size > INT_MAX)
    {
        Scierror(34);
        return Function::Error;
    }

    // dimensions of output result
    int out_rows;
    int out_cols;

    if (in[0]->getAs<GenericType>()->getDims() == 2 &&
        in[0]->getAs<GenericType>()->getRows() == 1 &&
        in[0]->getAs<GenericType>()->getCols() >= 1)
    {
        // row vector
        out_rows = 1;
        out_cols = out_size;
    }
    else
    {
        // column vector
        out_rows = out_size;
        out_cols = 1;
    }

    InternalType::ScilabType out_type = found->second.first;
    InternalType::ScilabType in_type = in[0]->getType();
    
    // if we need not to cast, then the output needs only a reshape
    if (in_type == out_type)
    {
        // InternalType* result = in[0]->getRef() > 0 ? in[0]->clone() : in[0];
        // FIXME: "reshape" uses the dreadful "checkRef" feature (cf. #137), which
        // is Ok in this context, but things may change in the future ...
        int dims[2] = {out_rows, out_cols};
        InternalType* result = in[0]->getAs<GenericType>()->reshape(dims, 2);
        out.push_back(result);
        return Function::OK;
    }

    // ptr to input data
    void* in_data = NULL;

    switch(in_type)
    {
        case InternalType::ScilabBool:
            in_data = in[0]->getAs<Bool>()->get();
            break;
        case InternalType::ScilabInt8:
            in_data = in[0]->getAs<Int8>()->get();
            break;
        case InternalType::ScilabInt16:
            in_data = in[0]->getAs<Int16>()->get();
            break;
        case InternalType::ScilabInt32:
            in_data = in[0]->getAs<Int32>()->get();
            break;
        case InternalType::ScilabInt64:
            in_data = in[0]->getAs<Int64>()->get();
            break;
        case InternalType::ScilabUInt8:
            in_data = in[0]->getAs<UInt8>()->get();
            break;
        case InternalType::ScilabUInt16:
            in_data = in[0]->getAs<UInt16>()->get();
            break;
        case InternalType::ScilabUInt32:
            in_data = in[0]->getAs<UInt32>()->get();
            break;
        case InternalType::ScilabUInt64:
            in_data = in[0]->getAs<UInt64>()->get();
            break;
        case InternalType::ScilabDouble:
            in_data = in[0]->getAs<Double>()->get();
            break;
        
        default:
            // unknown error
            Scierror(0);
            return Function::Error;
    }
    
    // ptr to output data
    void* out_data = NULL;
    InternalType* result = NULL;

    switch(out_type)
    {
        case InternalType::ScilabBool:
            result = new Bool(out_rows, out_cols, reinterpret_cast<int**>(&out_data));
            break;
        case InternalType::ScilabInt8:
            result = new Int8(out_rows, out_cols, reinterpret_cast<char**>(&out_data));
            break;
        case InternalType::ScilabInt16:
            result = new Int16(out_rows, out_cols, reinterpret_cast<short int**>(&out_data));
            break;
        case InternalType::ScilabInt32:
            result = new Int32(out_rows, out_cols, reinterpret_cast<int**>(&out_data));
            break;
        case InternalType::ScilabInt64:
            result = new Int64(out_rows, out_cols, reinterpret_cast<long long int**>(&out_data));
            break;
        case InternalType::ScilabUInt8:
            result = new UInt8(out_rows, out_cols, reinterpret_cast<unsigned char**>(&out_data));
            break;
        case InternalType::ScilabUInt16:
            result = new UInt16(out_rows, out_cols, reinterpret_cast<short unsigned int**>(&out_data));
            break;
        case InternalType::ScilabUInt32:
            result = new UInt32(out_rows, out_cols, reinterpret_cast<unsigned int**>(&out_data));
            break;
        case InternalType::ScilabUInt64:
            result = new UInt64(out_rows, out_cols, reinterpret_cast<long long unsigned int**>(&out_data));
            break;
        case InternalType::ScilabDouble:
            result = new Double(out_rows, out_cols, reinterpret_cast<double**>(&out_data));
            break;
        
        default:
            // unknown error
            Scierror(0);
            return Function::Error;
    }
    
    memcpy(out_data, in_data, in_bytes);

    out.push_back(result);
    return Function::OK;
}

int bytes_of_data(InternalType* in)
{
    int byte_size;
    int dummy;
    in->getMemory(&byte_size, &dummy);
    return byte_size;
}
