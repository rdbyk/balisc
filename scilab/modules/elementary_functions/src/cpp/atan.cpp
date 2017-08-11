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

#include "atan.hxx"

#include <complex>
#include <cmath>

extern "C"
{
#include "balisc_elementary.h"
}

using types::Double;

namespace balisc
{

Double* atan_real(Double* x)
{
    int n = x->getSize();
    
    Double* y = new Double(x->getDims(), x->getDimsArray(), false);
    
    double* xr = x->get();
    double* yr = y->get();

#if !defined(balisc_atan_m128d)
    for (int i = 0; i < n; i++)
    {
        yr[i] = balisc_atan_d(xr[i]);
    }
#else
    int n2 = n - 1;
                
    switch (n & 0x1)
    {
        case 1:
            yr[n2] = balisc_atan_d(xr[n2]);
        default:
            for (int i = 0; i < n2; i++)
            {
                __m128d a = balisc_atan_m128d(*((__m128d*)&(xr[i])));
                yr[i] = a[0];
                yr[++i] = a[1];
            }
    }
#endif

    return y;
}


Double* atan2(Double* x1, Double* x2)
{
    int n = x1->getSize();
    
    Double* y = new Double(x1->getDims(), x1->getDimsArray(), false);
    
    double* x1r = x1->get();
    double* x2r = x2->get();
    double* yr = y->get();

#if !defined(balisc_atan2_m128d)
    for (int i = 0; i < n; i++)
    {
        yr[i] = ::balisc_atan2_d(x1r[i], x2r[i]);
    }
#else
    int n2 = n - 1;
                
    switch (n & 0x1)
    {
        case 1:
            yr[n2] = ::balisc_atan2_d(x1r[n2], x2r[n2]);
        default:
            for (int i = 0; i < n2; i++)
            {
                __m128d a = ::balisc_atan2_m128d(*((__m128d*)&(x1r[i])), *((__m128d*)&(x2r[i])));
                yr[i] = a[0];
                yr[++i] = a[1];
            }
    }
#endif

    return y;
}

}
