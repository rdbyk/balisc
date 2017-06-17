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

#include "tan.hxx"
#include <cmath>
#include <Eigen/Core>

using types::Double;

using Eigen::Map;
using Eigen::ArrayXd;
using Eigen::ArrayXcd;

namespace balisc
{

static inline std::complex<double> __tan__(double re, double im)
{
    return std::tan(std::complex<double>(re, im));
}

Double* tan(Double* x)
{
    bool is_complex = x->isComplex();
    Double* y = new Double(x->getDims(), x->getDimsArray(), is_complex);
    
    int n = x->getSize();

    if (is_complex)
    {
        //Map<ArrayXd> xr(x->get(), n);
        //Map<ArrayXd> xi(x->getImg(), n);
        //Map<ArrayXd> yr(y->get(), n);
        //Map<ArrayXd> yi(y->getImg(), n);
        //ArrayXcd tmp(n);
        //tmp = xr.binaryExpr<std::complex<double>(*)(double,double)>(xi, &__tan__);
        //yr = tmp.real();
        //yi = tmp.imag();

        double* xr = x->get();
        double* xi = x->getImg();
        double* yr = y->get();
        double* yi = y->getImg();
        
        for (int i = 0; i < n; i++)
        {
            std::complex<double> lz(std::tan(std::complex<double>(xr[i], xi[i])));
            yr[i] = lz.real();
            yi[i] = lz.imag();
        }
        
        return y;
    }
    else
    {
        //Map<ArrayXd> xr(x->get(), n);
        //Map<ArrayXd> yr(y->get(), n);
        //yr = xr.tan();
    
        double* xr = x->get();
        double* yr = y->get();
    
        for (int i = 0; i < n; i++)
        {
            yr[i] = std::tan(xr[i]);
        }
    
        return y;
    }
}

}
