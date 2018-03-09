// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
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

#include "sin.hxx"

extern "C"
{
#include "balisc_elementary.h"
}

using types::Double;

namespace balisc
{

Double* sin(Double* x)
{
    bool is_complex = x->isComplex();

    Double* y =  x->getRef() > 1 ? new Double(x->getDims(), x->getDimsArray(),is_complex) : x;

    int n = x->getSize();

    if (is_complex)
    {
        double* xr = x->get();
        double* yr = y->get();
        double* xi = x->getImg();
        double* yi = y->getImg();

        for (int i = 0; i < n; i++)
        {
#if !defined(balisc_sin_m128d)
            double a0 = ::balisc_exp_d(xi[i]);
            double a1 = 1 / a0;
            Sleef_double2 b = Sleef_sincos_u35(xr[i]);
            yr[i] = 0.5 * b.x * (a0 + a1);
            yi[i] = 0.5 * b.y * (a0 - a1);
#else
            double xi_i = xi[i];
            __m128d a = ::balisc_exp_m128d((__m128d){xi_i,-xi_i});
            Sleef_double2 b = Sleef_sincos_u35(xr[i]);
            yr[i] = 0.5 * b.x * (a[0] + a[1]);
            yi[i] = 0.5 * b.y * (a[0] - a[1]);
#endif
        }

        return y;
    }
    else
    {        
        double* xr = x->get();
        double* yr = y->get();

#if !defined(balisc_sin_m128d)
        for (int i = 0; i < n; i++)
        {
            yr[i] = ::balisc_sin_d(xr[i]);
        }
        return y;
#else
        int i = 0;
        for ( ; i < n - 1; i += 2)
        {
            __m128d a = ::balisc_sin_m128d(*((__m128d*)&(xr[i])));
            yr[i] = a[0];
            yr[i+1] = a[1];
        }

        if (n & 0x1)
        {
            yr[i] = ::balisc_sin_d(xr[i]);
            return y;
        }

        return y;
#endif
    }
}

}
