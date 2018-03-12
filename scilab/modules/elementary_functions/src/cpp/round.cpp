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
    Double* y = x->getRef() > 1 ? new Double(x->getDims(), x->getDimsArray(), is_complex) : x;

    int n = x->getSize();
    
    if (is_complex)
    {
        double* xr = x->get();
        double* yr = y->get();
        double* xi = x->getImg();
        double* yi = y->getImg();
        
        for (int i = 0; i < n; i++)
        {
#if !defined(balisc_round_m128d)
            yr[i] = ::balisc_round_d(xr[i]);
            yi[i] = ::balisc_round_d(xi[i]);
#else
            __m128d a = ::balisc_round_m128d((__m128d){xr[i],xi[i]});
            yr[i] = a[0];
            yi[i] = a[1];
#endif
        }
    }
    else
    {
        double* xr = x->get();
        double* yr = y->get();
        
#if !defined(balisc_round_m128d)
        for (int i = 0; i < n; i++)
        {
            yr[i] = ::balisc_round_d(xr[i]);
        }

        return y;
#elif !defined(balisc_round_m256d)
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

        return y;
#else
        int i = 0;
        for ( ; i < n - 3; i += 4)
        {
            __m256d a = ::balisc_round_m256d(_mm256_loadu_pd(&(xr[i])));
            yr[i] = a[0];
            yr[i+1] = a[1];
            yr[i+2] = a[2];
            yr[i+3] = a[3];
        }

        switch (n % 4)
        {
            case 1:
                yr[i] = ::balisc_round_d(xr[i]);
                return y;

            case 2:
                {
                    __m128d a = ::balisc_round_m128d(*((__m128d*)&(xr[i])));
                    yr[i] = a[0];
                    yr[i+1] = a[1];
                }
                return y;

            case 3:
                {
                    __m128d a = ::balisc_round_m128d(*((__m128d*)&(xr[i])));
                    yr[i] = a[0];
                    yr[i+1] = a[1];
                    yr[i+2] = ::balisc_round_d(xr[i+2]);
                }
                return y;
        }

        return y;
#endif
    }

    return y;
}

}
