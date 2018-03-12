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

#include "atan.hxx"

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
            return y;
#elif !defined(balisc_atan_m256d)
            int i = 0;
            for ( ; i < n - 1; i += 2)
            {
                __m128d a = balisc_atan_m128d(*((__m128d*)&(xr[i])));
                yr[i] = a[0];
                yr[i+1] = a[1];
            }

            if (n & 0x1)
            {
                yr[i] = balisc_atan_d(xr[i]);
                return y;
            }

            return y;
#else
        int i = 0;
        for ( ; i < n - 3; i += 4)
        {
            __m256d a = ::balisc_atan_m256d(_mm256_loadu_pd(&(xr[i])));
            yr[i] = a[0];
            yr[i+1] = a[1];
            yr[i+2] = a[2];
            yr[i+3] = a[3];
        }

        switch (n % 4)
        {
            case 1:
                yr[i] = ::balisc_atan_d(xr[i]);
                return y;

            case 2:
                {
                    __m128d a = ::balisc_atan_m128d(*((__m128d*)&(xr[i])));
                    yr[i] = a[0];
                    yr[i+1] = a[1];
                }
                return y;

            case 3:
                {
                    __m128d a = ::balisc_atan_m128d(*((__m128d*)&(xr[i])));
                    yr[i] = a[0];
                    yr[i+1] = a[1];
                    yr[i+2] = ::balisc_atan_d(xr[i+2]);
                }
                return y;
        }

        return y;
#endif
}

bool atan_singularity(Double* x)
{
    int n = x->getSize();
    
    double* xr = x->get();
    double* xi = x->getImg();
    
    for (int i = 0; i < n; i++)
    {
        if (xr[i] == 0 && xi[i] == 1)
        {
            return true;
        }
    }
    
    return false;
}

Double* atan_complex(Double* x)
{
    int n = x->getSize();
    
    Double* y = new Double(x->getDims(), x->getDimsArray(), true);
    
    double* xr = x->get();
    double* xi = x->getImg();
    double* yr = y->get();
    double* yi = y->getImg();
    
    for (int i = 0; i < n; i++)
    {
        double xr_i = xr[i];
        double xi_i = xi[i];
#if !defined(balisc_hypot_m128d)
        double cp = balisc_hypot_d(xr_i, xi_i + 1);
        double cn = balisc_hypot_d(xr_i, xi_i - 1);
        double a = cp / cn;
#else
        __m128d c = balisc_hypot_m128d((__m128d){xr_i, xr_i}, (__m128d){xi_i + 1, xi_i - 1});
        double a = c[0] / c[1];
#endif
        yr[i] = 0.5 * balisc_atan2_d(2 * xr_i, 1 - (xr_i * xr_i + xi_i * xi_i));
        yi[i] = 0.5 * balisc_log_d(a);
    }
    
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
            return y;
#elif !defined(balisc_atan2_m256d)
            int i = 0;
            for ( ; i < n - 1; i += 2)
            {
                __m128d a = ::balisc_atan2_m128d(*((__m128d*)&(x1r[i])), *((__m128d*)&(x2r[i])));
                yr[i] = a[0];
                yr[i+1] = a[1];
            }

            if (n & 0x1)
            {
                yr[i] = ::balisc_atan2_d(x1r[i], x2r[i]);
                return y;
            }

            return y;
#else
        int i = 0;
        for ( ; i < n - 3; i += 4)
        {
            __m256d a = ::balisc_atan2_m256d(_mm256_loadu_pd(&(x1r[i])), _mm256_loadu_pd(&(x2r[i])));
            yr[i] = a[0];
            yr[i+1] = a[1];
            yr[i+2] = a[2];
            yr[i+3] = a[3];
        }

        switch (n % 4)
        {
            case 1:
                yr[i] = ::balisc_atan2_d(x1r[i], x2r[i]);
                return y;

            case 2:
                {
                    __m128d a = ::balisc_atan2_m128d(*((__m128d*)&(x1r[i])), *((__m128d*)&(x2r[i])));
                    yr[i] = a[0];
                    yr[i+1] = a[1];
                }
                return y;

            case 3:
                {
                    __m128d a = ::balisc_atan2_m128d(*((__m128d*)&(x1r[i])), *((__m128d*)&(x2r[i])));
                    yr[i] = a[0];
                    yr[i+1] = a[1];
                    yr[i+2] = ::balisc_atan2_d(x1r[i+2], x2r[i+2]);
                }
                return y;
        }

        return y;
#endif
}

}
