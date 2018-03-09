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

#include "sqrt.hxx"
#include <cmath>
#include <Eigen/Core>

using types::Double;

using Eigen::Map;
using Eigen::ArrayXd;
using Eigen::ArrayXcd;

namespace balisc
{

static inline std::complex<double> __sqrt__(double re, double im)
{
    if (im != 0)
    {
        return std::sqrt(std::complex<double>(re, im));
    }
    else
    {
        // http://bugzilla.scilab.org/show_bug.cgi?id=13111
        return std::sqrt(std::complex<double>(re, +0.0));
    }
}

Double* sqrt(Double* x)
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
        tmp = xr.binaryExpr<std::complex<double>(*)(double,double)>(xi, &__sqrt__);
        yr = tmp.real();
        yi = tmp.imag();
        
        return y;
    }
    else
    {
        double* xr = x->get();
        
        for (int i = 0; i < n; ++i)
        {
            if (xr[i] < 0)
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
            
            double xr_i;                
            for (int i = 0; i < n; i++)
            {
                xr_i = xr[i];
                if(xr_i < 0)
                {
                    yr[i] = 0.0;
                    yi[i] = std::sqrt(-xr_i);
                }
                else
                {
                    yr[i] = std::sqrt(xr_i);
                    yi[i] = 0.0;
                }
            }
        }
        else
        {
            Map<ArrayXd> xr(x->get(), n);
            Map<ArrayXd> yr(y->get(), n);
            yr = xr.sqrt();
        }

        return y;
    }
}

}
