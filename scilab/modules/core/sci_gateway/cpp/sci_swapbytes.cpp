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
using types::typed_list;
using types::UInt8;
using types::UInt16;
using types::UInt32;
using types::UInt64;


static int bytes_of_data(InternalType* in);

Function::ReturnValue sci_swapbytes(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71, 1);
        return Function::Error;
    }
    
    if (!in[0]->isBool() && !in[0]->isInt() && !in[0]->isDouble())
    {
        Scierror(90, 1, _("real, complex, integer, or boolean"));
        return Function::Error;
    }

    if (in[0]->isDouble() && in[0]->getAs<Double>()->isEmpty())
    {
        out.push_back(Double::Empty());
        return Function::OK;
    }

    int in_bytes_of_data = bytes_of_data(in[0]);
    int in_bytes = in[0]->getAs<GenericType>()->isComplex() ? in_bytes_of_data / 2 : in_bytes_of_data;
    
    if (in_bytes == in[0]->getAs<GenericType>()->getSize())
    {
        out.push_back(in[0]);
        return Function::OK;
    }

    // copy input to result
    InternalType* res = in[0]->getRef() > 0 ? in[0]->clone() : in[0];
    
    // ptr to res data
    void* res_data = NULL;
    void* res_data_img = NULL;
    
    switch(res->getType())
    {
        case InternalType::ScilabBool:
            res_data = res->getAs<Bool>()->get();
            break;
        case InternalType::ScilabInt8:
            res_data = res->getAs<Int8>()->get();
            break;
        case InternalType::ScilabInt16:
            res_data = res->getAs<Int16>()->get();
            break;
        case InternalType::ScilabInt32:
            res_data = res->getAs<Int32>()->get();
            break;
        case InternalType::ScilabInt64:
            res_data = res->getAs<Int64>()->get();
            break;
        case InternalType::ScilabUInt8:
            res_data = res->getAs<UInt8>()->get();
            break;
        case InternalType::ScilabUInt16:
            res_data = res->getAs<UInt16>()->get();
            break;
        case InternalType::ScilabUInt32:
            res_data = res->getAs<UInt32>()->get();
            break;
        case InternalType::ScilabUInt64:
            res_data = res->getAs<UInt64>()->get();
            break;
        case InternalType::ScilabDouble:
            res_data = res->getAs<Double>()->get();
            res_data_img = res->getAs<Double>()->getImg();
            break;
        
        default:
            // unknown error
            Scierror(0);
            return Function::Error;
    }
    
    // swap bytes of result data
    int bytes_element = in_bytes / res->getAs<GenericType>()->getSize();
    unsigned char* res_byte = reinterpret_cast<unsigned char*>(res_data);
    unsigned char* res_byte_img = reinterpret_cast<unsigned char*>(res_data_img);
    
    // FIXME: this is a naive implementation, which should/could be
    // replaced by something more performant ...
    if (res_data_img ==  NULL)
    {
        for (int i = 0; i < res->getAs<GenericType>()->getSize(); ++i)
        {
            int b = i * bytes_element;
            int e = b + bytes_element - 1;

            // reverse byte order of element "i"
            for (int j = 0; j < bytes_element / 2; ++j)
            {
                int bj = b + j;
                int ej = e - j;
                unsigned char tmp = res_byte[bj];
                res_byte[bj] = res_byte[ej];
                res_byte[ej] = tmp;
            }
        }
    }
    else
    {
        for (int i = 0; i < res->getAs<GenericType>()->getSize(); ++i)
        {
            int b = i * bytes_element;
            int e = b + bytes_element - 1;

            // reverse byte order of element "i"
            for (int j = 0; j < bytes_element / 2; ++j)
            {
                int bj = b + j;
                int ej = e - j;
                unsigned char tmp = res_byte[bj];
                res_byte[bj] = res_byte[ej];
                res_byte[ej] = tmp;
                tmp = res_byte_img[bj];
                res_byte_img[bj] = res_byte_img[ej];
                res_byte_img[ej] = tmp;
            }
        }
    }

    out.push_back(res);
    return Function::OK;
}

int bytes_of_data(InternalType* in)
{
    int byte_size;
    int dummy;
    in->getMemory(&byte_size, &dummy);
    return byte_size;
}
