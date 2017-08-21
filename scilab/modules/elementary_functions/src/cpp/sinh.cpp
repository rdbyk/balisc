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

#include "sinh.hxx"
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

Double* sinh(Double* x)
{
    bool is_complex = x->isComplex();
    Double* y = new Double(x->getDims(), x->getDimsArray(),is_complex);
     
    int n = x->getSize();
    
    if (is_complex)
    {
        double* xr = x->get();
        double* yr = y->get();
        double* xi = x->getImg();
        double* yi = y->getImg();

        for (int i = 0; i < n; i++)
        {
#if !defined(balisc_exp_m128d)
            double a0 = ::balisc_exp_d(xr[i]);
            double a1 = 1 / a0;
            Sleef_double2 b = Sleef_sincos_u35(xi[i]);
            yr[i] = 0.5 * b.y * (a0 - a1);
            yi[i] = 0.5 * b.x * (a0 + a1);
#else
            double xr_i = xr[i];
            __m128d a = ::balisc_exp_m128d((__m128d){xr_i,-xr_i});
            Sleef_double2 b = Sleef_sincos_u35(xi[i]);
            yr[i] = 0.5 * b.y * (a[0] - a[1]);
            yi[i] = 0.5 * b.x * (a[0] + a[1]);
#endif
        }

        return y;
    }
    else
    {
        Map<ArrayXd> xr(x->get(), n);
        Map<ArrayXd> yr(y->get(), n);
        ArrayXd e(xr.exp());
        yr = 0.5 * (e - 1/e);
        
        return y;
    }
}

}
