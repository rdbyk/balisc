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

#include "asin.hxx"

#include <complex>
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
            std::complex<double> z(std::asin(std::complex<double>(xr[i], xi[i])));
            yr[i] = z.real();
            yi[i] = z.imag();
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
            
            double* xr = x->get();
            double* yr = y->get();
            
#if !defined(balisc_asin_m128d)
            for (int i = 0; i < n; i++)
            {
                yr[i] = balisc_asin_d(xr[i]);
            }
            return y;
#else
            int i;
            for (i = 0; i < n - 1; i++)
            {
                __m128d a = balisc_asin_m128d(*((__m128d*)&(xr[i])));
                yr[i] = a[0];
                yr[++i] = a[1];
            }

            for ( ; i < n; i++)
            {
                yr[i] = balisc_asin_d(xr[i]);
            }
            
            return y;
#endif
        }
    }
}

}
