// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2017 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
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

#include "tanh.hxx"
#include <cmath>
#include <Eigen/Core>

using types::Double;

using Eigen::Map;
using Eigen::ArrayXd;
using Eigen::ArrayXcd;

namespace balisc
{

static inline std::complex<double> __tanh__(double re, double im)
{
    std::complex<double> z(re, im);
    return tanh(z);
}

Double* tanh(Double* x)
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
        ArrayXcd tmp(n);
        tmp = xr.binaryExpr<std::complex<double>(*)(double,double)>(xi, &__tanh__);
        yr = tmp.real();
        yi = tmp.imag();
        
        return y;
    }
    else
    {
        Map<ArrayXd> xr(x->get(), n);
        Map<ArrayXd> yr(y->get(), n);
        yr = xr.tanh();
        
        return y;
    }
}

}
