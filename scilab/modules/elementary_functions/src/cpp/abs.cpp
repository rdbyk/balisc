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

#include "abs.hxx"

extern "C"
{
#include "balisc_elementary.h"
}

using types::Double;

namespace balisc
{

Double* abs(Double* x)
{
    Double* y =  x->getRef() > 1 ? new Double(x->getDims(), x->getDimsArray()) : x;

    int n = x->getSize();
    
    if (x->isComplex())
    {
        double* xr = x->get();
        double* xi = x->getImg();
        double* yr = y->get();
        
#if !defined(balisc_hypot_m128d)
        for (int i = 0; i < n; i++)
        {
            yr[i] = ::balisc_hypot_d(xr[i], xi[i]);
        }
#else
        int n2 = n - 1;
                    
        switch (n & 0x1)
        {
            case 1:
                yr[n2] = ::balisc_hypot_d(xr[n2], xi [n2]);
            default:
                for (int i = 0; i < n2; i++)
                {
                    __m128d a = ::balisc_hypot_m128d(*((__m128d*)&(xr[i])), *((__m128d*)&(xi[i])));
                    yr[i] = a[0];
                    yr[++i] = a[1];
                }
        }
#endif
        y->setComplex(false);

        return y;
    }
    else
    {
        double* xr = x->get();
        double* yr = y->get();

#if !defined(balisc_fabs_m128d)
        for (int i = 0; i < n; i++)
        {
            yr[i] = ::balisc_fabs_d(xr[i]);
        }
#else
        int n2 = n - 1;
                    
        switch (n & 0x1)
        {
            case 1:
                yr[n2] = ::balisc_fabs_d(xr[n2]);
            default:
                for (int i = 0; i < n2; i++)
                {
                    __m128d a = ::balisc_fabs_m128d(*((__m128d*)&(xr[i])));
                    yr[i] = a[0];
                    yr[++i] = a[1];
                }
        }
#endif

        return y;
    }

}

}
