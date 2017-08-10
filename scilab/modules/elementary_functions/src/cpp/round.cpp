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

#include "round.hxx"

extern "C"
{
#include "balisc_elementary.h"
}

using types::Double;

namespace balisc
{

Double* round(Double* x)
{
    bool is_complex = x->isComplex();
    int n = x->getSize();
    
    if (is_complex)
    {
        Double* y = new Double(x->getDims(), x->getDimsArray(), is_complex);
        
        double* xr = x->get();
        double* yr = y->get();
        double* xi = x->getImg();
        double* yi = y->getImg();
        
        for (int i = 0; i < n; i++)
        {
            yr[i] = ::balisc_round_d(xr[i]);
            yi[i] = ::balisc_round_d(xi[i]);
        }
        
        return y;
    }
    else
    {
        Double* y = new Double(x->getDims(), x->getDimsArray(), is_complex);
        
        double* xr = x->get();
        double* yr = y->get();
        
#if !defined(balisc_round_m128d)
        for (int i = 0; i < n; i++)
        {
            yr[i] = ::balisc_round_d(xr[i]);
        }
#else
        int i;
        for (i = 0; i < n - 1; i++)
        {
            __m128d a = ::balisc_round_m128d(*((__m128d*)&(xr[i])));
            yr[i] = a[0];
            yr[++i] = a[1];
        }

        for ( ; i < n; i++)
        {
            yr[i] = ::balisc_round_d(xr[i]);
        }
#endif
        return y;
    }
}

}
