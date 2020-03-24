// Balisc (https://github.com/rdbyk/balisc/)
//
// Copyright (C) 2020 - Dirk Reusch, Kybernetik Dr. Reusch
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

static std::map<std::wstring, std::pair<InternalType::ScilabType,int>> unpack_types = {
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

Function::ReturnValue sci_bitunpack(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71, 1);
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

    if (in[0]->isDouble() && in[0]->getAs<Double>()->isEmpty())
    {
        out.push_back(Double::Empty());
        return Function::OK;
    }
    
    // calculate and check size of output
    int in_bytes = bytes_of_data(in[0]);
    size_t out_size = ((size_t)CHAR_BIT) * in_bytes;

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

    // ptr to input data
    void* in_data = NULL;
    InternalType::ScilabType in_type = in[0]->getType();

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
    types::UInt8* result = new UInt8(out_rows, out_cols);
    void* out_data = result->get();

    for (int i = 0; i < in_bytes; ++i)
    {
        char b = ((char*)in_data)[i];
        int k = i * CHAR_BIT;
        for (int j = 0; j < CHAR_BIT; ++j)
            ((char*)out_data)[k + j] = (b & (1 << j)) != 0;
    }

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
