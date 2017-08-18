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

#include "sin.hxx"
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

Double* sin(Double* x)
{
    bool is_complex = x->isComplex();
    Double* y = new Double(x->getDims(), x->getDimsArray(),is_complex);
     
    int n = x->getSize();
    
    if (is_complex)
    {
        Map<ArrayXd> xr(x->get(), n);
        Map<ArrayXd> xi(x->getImg(), n);
        Map<ArrayXd> yr(y->get(), n);
        Map<ArrayXd> yi(y->getImg(), n);
        ArrayXd ep(xi.exp());
        ArrayXd en(ep.inverse());
        yr = 0.5 * xr.sin() * (ep + en);
        yi = 0.5 * xr.cos() * (ep - en);
        
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
