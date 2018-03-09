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

#include "exp.hxx"

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

Double* exp(Double* x)
{
    bool is_complex = x->isComplex();
    Double* y =  x->getRef() > 1 ? new Double(x->getDims(), x->getDimsArray(), is_complex) : x;
    
    int n = x->getSize();
    
    if (is_complex)
    {
        double* xr = x->get();
        double* yr = y->get();
        double* xi = x->getImg();
        double* yi = y->getImg();
        
        for (int i = 0; i < n; i++)
        {   
            double r = ::balisc_exp_d(xr[i]);
            Sleef_double2 a = Sleef_sincos_u35(xi[i]);
            yr[i] = r * a.y;
            yi[i] = r * a.x;
        }        
        
        return y;
    }
    else
    {
        Map<ArrayXd> xr(x->get(), n);
        Map<ArrayXd> yr(y->get(), n);
        yr = xr.exp();

        return y;
    }
}

}
