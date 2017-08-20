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

#include "tan.hxx"

#include <complex>
#include <cmath>

extern "C"
{
#include "balisc_elementary.h"
}

using types::Double;

namespace balisc
{

Double* tan(Double* x)
{
    bool is_complex = x->isComplex();
    Double* y = new Double(x->getDims(), x->getDimsArray(), is_complex);
    
    int n = x->getSize();

    if (is_complex)
    {
        double* xr = x->get();
        double* xi = x->getImg();
        double* yr = y->get();
        double* yi = y->getImg();
        
        for (int i = 0; i < n; i++)
        {
            std::complex<double> lz(std::tan(std::complex<double>(xr[i], xi[i])));
            yr[i] = lz.real();
            yi[i] = lz.imag();
        }
        
        return y;
    }
    else
    {
        double* xr = x->get();
        double* yr = y->get();

#if !defined(balisc_tan_m128d)
        for (int i = 0; i < n; i++)
        {
            yr[i] = ::balisc_tan_d(xr[i]);
        }
        return y;
#else
        int i = 0;
        for ( ; i < n - 1; i += 2)
        {
            __m128d a = ::balisc_tan_m128d(*((__m128d*)&(xr[i])));
            yr[i] = a[0];
            yr[i+1] = a[1];
        }

        if (n & 0x1)
        {
            yr[i] = ::balisc_tan_d(xr[i]);
            return y;
        }

        return y;
#endif
    }
}

}
