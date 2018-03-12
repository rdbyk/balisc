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

#include "log10.hxx"

#include <complex>
#include <cmath>
#include <Eigen/Core>

extern "C"
{
#include "balisc_elementary.h"
}

using types::Double;

using Eigen::Map;
using Eigen::ArrayXd;
using Eigen::ArrayXcd;

namespace balisc
{

static inline std::complex<double> __log10__(double re, double im)
{
    return std::log10(std::complex<double>(re, im));
}

Double* log10(Double* x)
{
    bool is_complex = x->isComplex();
    int n = x->getSize();
    
    if (is_complex)
    {
        Double* y = x->getRef() > 1 ? new Double(x->getDims(), x->getDimsArray(), true) : x;
        
        Map<ArrayXd> xr(x->get(), n);
        Map<ArrayXd> xi(x->getImg(), n);
        Map<ArrayXd> yr(y->get(), n);
        Map<ArrayXd> yi(y->getImg(), n);
        ArrayXcd tmp(n);
        tmp = xr.binaryExpr<std::complex<double>(*)(double,double)>(xi, &__log10__);
        yr = tmp.real();
        yi = tmp.imag();
        
        return y;
    }
    else
    {
        double* xr = x->get();
        
        for (int i = 0; i < n; i++)
        {
            if (xr[i] < 0.0)
            {
                is_complex = true;
                break;
            }
        }

        Double* y = x->getRef() > 1 ? new Double(x->getDims(), x->getDimsArray()) : x;

        if (is_complex)
        {
            y->setComplex(true);

            double* yr = y->get();
            double* yi = y->getImg();
            
            for (int i = 0; i < n; i++)
            {
                double xr_i = xr[i];
                
                if (xr_i >= 0)
                {
                    yr[i] = ::balisc_log10_d(xr_i);
                    yi[i] = 0.0;
                }
                else
                {
                    yr[i] = ::balisc_log10_d(-xr_i);
                    yi[i] = M_PI / M_LN10;
                }
            }
        }
        else
        {
            double* xr = x->get();
            double* yr = y->get();

#if !defined(balisc_log10_m128d)
            for (int i = 0; i < n; i++)
            {
                yr[i] = ::balisc_log10_d(xr[i]);
            }
            return y;
#elif !defined(balisc_log10_m256d)
            int i;
            for (i = 0; i < n - 1; i++)
            {
                __m128d a = ::balisc_log10_m128d(*((__m128d*)&(xr[i])));
                yr[i] = a[0];
                yr[++i] = a[1];
            }

            for ( ; i < n; i++)
            {
                yr[i] = ::balisc_log10_d(xr[i]);
            }

            return y;
#else
            int i = 0;
            for ( ; i < n - 3; i += 4)
            {
                __m256d a = ::balisc_log10_m256d(_mm256_loadu_pd(&(xr[i])));
                yr[i] = a[0];
                yr[i+1] = a[1];
                yr[i+2] = a[2];
                yr[i+3] = a[3];
            }

            switch (n % 4)
            {
                case 1:
                    yr[i] = ::balisc_log10_d(xr[i]);
                    return y;

                case 2:
                    {
                        __m128d a = ::balisc_log10_m128d(*((__m128d*)&(xr[i])));
                        yr[i] = a[0];
                        yr[i+1] = a[1];
                    }
                    return y;

                case 3:
                    {
                        __m128d a = ::balisc_log10_m128d(*((__m128d*)&(xr[i])));
                        yr[i] = a[0];
                        yr[i+1] = a[1];
                        yr[i+2] = ::balisc_log10_d(xr[i+2]);
                    }
                    return y;
            }

            return y;
#endif
        }

        return y;
    }
}

}
