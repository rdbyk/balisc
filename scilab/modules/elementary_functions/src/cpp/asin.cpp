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

#include "asin.hxx"

#include <cmath>

extern "C"
{
#include "balisc_elementary.h"
}

using types::Double;

namespace balisc
{

Double* asin(Double* x)
{
    bool is_complex = x->isComplex();
    int n = x->getSize();
    
    if (is_complex)
    {
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
            double cp = balisc_hypot_d(xr_i + 1, xi_i);
            double cn = balisc_hypot_d(xr_i - 1, xi_i);
            double a = 0.5 * (cp + cn);
            double b = 0.5 * (cp - cn);
#else
            __m128d c = balisc_hypot_m128d((__m128d){xr_i + 1, xr_i - 1}, (__m128d){xi_i, xi_i});
            double a = 0.5 * (c[0] + c[1]);
            double b = 0.5 * (c[0] - c[1]);
#endif
            double im = balisc_log_d(a + balisc_sqrt_d(a * a - 1));

            yr[i] = balisc_asin_d(b);

            if (xi_i < 0)
            {
                yi[i] = im;
            }
            else
            {
                yi[i] = -im;
            }
        }
        
        return y;
    }
    else
    {
        double* xr = x->get();
        
        for (int i = 0; i < n; i++)
        {
            if (balisc_fabs_d(xr[i]) > 1.0)
            {
                is_complex = true;
                break;
            }
        }
        
        if (is_complex)
        {
            Double* y = new Double(x->getDims(), x->getDimsArray(), true);
            
            double* yr = y->get();
            double* yi = y->getImg();
            
            for (int i = 0; i < n; i++)
            {
                double xr_i = xr[i];
                
                if (xr_i > 1.0)
                {
                    yr[i] = M_PI_2;
                    yi[i] = -balisc_log_d(xr_i + balisc_sqrt_d(xr_i*xr_i - 1.0));
                }
                else if (xr_i < -1.0)
                {
                    yr[i] = - M_PI_2;
                    yi[i] = balisc_log_d(balisc_sqrt_d(xr_i*xr_i - 1.0) - xr_i);
                }
                else
                {
                    yr[i] = balisc_asin_d(xr_i);
                    yi[i] = 0.0;
                }
            }
            
            return y;
        }
        else
        {
            Double* y = new Double(x->getDims(), x->getDimsArray(), false);

            double* yr = y->get();
            
#if !defined(balisc_asin_m128d)
            for (int i = 0; i < n; i++)
            {
                yr[i] = balisc_asin_d(xr[i]);
            }
            return y;
#elif !defined(balisc_asin_m256d)
            int i = 0;
            for ( ; i < n - 1; i += 2)
            {
                __m128d a = balisc_asin_m128d(*((__m128d*)&(xr[i])));
                yr[i] = a[0];
                yr[i+1] = a[1];
            }

            if (n & 0x1)
            {
                yr[i] = balisc_asin_d(xr[i]);
                return y;
            }
            
            return y;
#else
        int i = 0;
        for ( ; i < n - 3; i += 4)
        {
            __m256d a = ::balisc_asin_m256d(_mm256_loadu_pd(&(xr[i])));
            yr[i] = a[0];
            yr[i+1] = a[1];
            yr[i+2] = a[2];
            yr[i+3] = a[3];
        }

        switch (n % 4)
        {
            case 1:
                yr[i] = ::balisc_asin_d(xr[i]);
                return y;

            case 2:
                {
                    __m128d a = ::balisc_asin_m128d(*((__m128d*)&(xr[i])));
                    yr[i] = a[0];
                    yr[i+1] = a[1];
                }
                return y;

            case 3:
                {
                    __m128d a = ::balisc_asin_m128d(*((__m128d*)&(xr[i])));
                    yr[i] = a[0];
                    yr[i+1] = a[1];
                    yr[i+2] = ::balisc_asin_d(xr[i+2]);
                }
                return y;
        }

        return y;
#endif
        }
    }
}

}
