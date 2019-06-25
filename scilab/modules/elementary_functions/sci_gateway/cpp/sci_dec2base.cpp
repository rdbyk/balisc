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

static wchar_t digit[] = L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static wchar_t* ull_to_base_n(unsigned long long v, int b, int len);
static wchar_t* dbl_to_base_n(double v, int b, int len);

template<typename T> 
String* matrix_to_base_n(T* m, int b, int n)
{
    String* s = new String(m->getDims(), m->getDimsArray());

    for (int i = 0; i < s->getSize(); ++i)
    {
        auto v = m->get(i);

        if (v >= 0)
        {
            wchar_t* ss = ull_to_base_n(v, b ,n);

            if (ss)
            {
                s->set(i, ss);
                FREE(ss);
            }
            else
            {
                delete s;
                Scierror(1);
                return NULL;
            }
        }
        else
        {
            delete s;
            Scierror(110, 1, _("non-negative integer values"));
            return NULL;
        }
    }

    return s;
}

template<> 
String* matrix_to_base_n<Double>(Double* m, int b, int n)
{
    String* s = new String(m->getDims(), m->getDimsArray());

    for (int i = 0; i < s->getSize(); ++i)
    {
        double v = m->get(i);
        
        if (v >= 0.0 && v == ceil(v) && isinf(v) == 0)
        {
            wchar_t* ss = dbl_to_base_n(v, b ,n);

            if (ss)
            {
                s->set(i, ss);
                FREE(ss);
            }
            else
            {
                delete s;
                Scierror(1);
                return NULL;
            }
        }
        else
        {
            delete s;
            Scierror(110, 1, _("non-negative integer values"));
            return NULL;
        }
    }

    return s;
}

Function::ReturnValue sci_dec2base(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() < 2 || in.size() > 3)
    {
        Scierror(72, 2, 3);
        return Function::Error;
    }

    int base = 2;

    if (in.size() >= 2)
    {
        if (in[0]->isInt() == false 
            && in[0]->isDouble() == false && in[0]->getAs<Double>()->isComplex() == true)
        {
            Scierror(90, 2, _("integer or real matrix"));
            return Function::Error;
        }
        
        if (in[1]->isDouble() == false && in[1]->getAs<Double>()->isScalar() == false)
        {
            Scierror(93, 1);
            return Function::Error;
        }
        
        base = static_cast<int>(in[1]->getAs<Double>()->getFirst());
        
        if (in[1]->getAs<Double>()->getFirst() != base || base < 2 || base > 36)
        {
            Scierror(110, 1, _("integer value from 2 to 36"));
            return Function::Error;
        }
    }
    
    int len = -1;

    if (in.size() == 3)
    {
        if (in[2]->isDouble() == false && in[2]->getAs<Double>()->isScalar() == false)
        {
            Scierror(93, 3);
            return Function::Error;
        }
        
        len = static_cast<int>(in[2]->getAs<Double>()->getFirst());
        
        if (in[2]->getAs<Double>()->getFirst() != len)
        {
            Scierror(111, 3);
            return Function::Error;
        }
    }

    if (in[0]->getAs<GenericType>()->getSize() == 0)
    {
        out.push_back(Double::Empty());
        return Function::OK;
    }

    String* result = NULL;

    switch(in[0]->getType())
    {
        case InternalType::ScilabInt8:
            result = matrix_to_base_n(in[0]->getAs<Int8>(), base, len);
            break;
        case InternalType::ScilabInt16:
            result = matrix_to_base_n(in[0]->getAs<Int16>(), base, len);
            break;
        case InternalType::ScilabInt32:
            result = matrix_to_base_n(in[0]->getAs<Int32>(), base, len);
            break;
        case InternalType::ScilabInt64:
            result = matrix_to_base_n(in[0]->getAs<Int64>(), base, len);
            break;
        case InternalType::ScilabUInt8:
            result = matrix_to_base_n(in[0]->getAs<UInt8>(), base, len);
            break;
        case InternalType::ScilabUInt16:
            result = matrix_to_base_n(in[0]->getAs<UInt16>(), base, len);
            break;
        case InternalType::ScilabUInt32:
            result = matrix_to_base_n(in[0]->getAs<UInt32>(), base, len);
            break;
        case InternalType::ScilabUInt64:
            result = matrix_to_base_n(in[0]->getAs<UInt64>(), base, len);
            break;
        case InternalType::ScilabDouble:
            result = matrix_to_base_n(in[0]->getAs<Double>(), base, len);
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
        // Scierror was set in 'matrix_to_base_n'
        return Function::Error;
    }
}

wchar_t* ull_to_base_n(unsigned long long v, int b, int len)
{
    int d = 1;
    unsigned long long m = static_cast<unsigned long long>(b);

    while (m <= v)
    {
        unsigned long long tmp = m * b;
        
        d++;

        if (tmp / b == m)
        {
            m = tmp;
        }
        else
        {
            break;
        }
    }

    int p = len - d;

    p = p < 0 ? 0 : p;
    
    int k = d + p;

    wchar_t* s  = (wchar_t*)MALLOC((k + 1) * sizeof(wchar_t));

    if (s)
    {
        s[k] = L'\0';

        while (--k >= p)
        {
            s[k] = digit[v % b];
            v /= b;
        }

        //  leading "zeros"
        while (--p >= 0)
        {
            s[p] = digit[0];
        }

        return s;
    }
    else
    {
        return NULL;
    }
}

wchar_t* dbl_to_base_n(double v, int b, int len)
{
    int d = 1;
    double m = static_cast<double>(b);

    while (m <= v)
    {
        m *= b;
        d++;
    }

    int p = len - d;

    p = p < 0 ? 0 : p;
    
    int k = d + p;

    wchar_t* s  = (wchar_t*)MALLOC((k + 1) * sizeof(wchar_t));

    if (s)
    {
        s[k] = L'\0';
        
        while (--k >= p)
        {
            double q = trunc(v / b);
            double r = v - q * b;
            // FIXME: is "ceil" here really needed?
            s[k] = digit[static_cast<int>(ceil(r))];
            v = q;
        }

        //  leading "zeros"
        while (--p >= 0)
        {
            s[p] = digit[0];
        }

        return s;
    }
    else
    {
        return NULL;
    }
}
