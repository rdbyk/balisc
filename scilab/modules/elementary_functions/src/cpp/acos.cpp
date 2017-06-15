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

#include "acos.hxx"
#include <cmath>
#include <Eigen/Core>

using types::Double;

using Eigen::Map;
using Eigen::ArrayXd;
using Eigen::ArrayXcd;

namespace balisc
{

static inline std::complex<double> __acos__(double re, double im)
{
    return std::acos(std::complex<double>(re, im));
}

Double* acos(Double* x)
{
    bool is_complex = x->isComplex();
    int n = x->getSize();
    
    if (n > 0)
    {
        if (is_complex)
        {
            Double* y = new Double(x->getDims(), x->getDimsArray(), true);
            
            Map<ArrayXd> xr(x->get(), n);
            Map<ArrayXd> xi(x->getImg(), n);
            Map<ArrayXd> yr(y->get(), n);
            Map<ArrayXd> yi(y->getImg(), n);
            ArrayXcd tmp(n);
//            tmp = xr.binaryExpr<std::complex<double>(*)(double,double)>(xi, &__acos__);
            tmp = log(tmp + sqrt(tmp*tmp -1));
            yr =   tmp.imag();
            yi = - tmp.real();

            //double* xr = x->get();
            //double* xi = x->getImg();
            //double* yr = y->get();
            //double* yi = y->getImg();
            
            //for (int i = 0; i < n; i++)
            //{
                //std::complex<double> lz(std::acos(std::complex<double>(xr[i], xi[i])));
                //yr[i] = lz.real();
                //yi[i] = lz.imag();
            //}
            
            return y;
        }
        else
        {
            double* xr = x->get();
            
            for (int i = 0; i < n; i++)
            {
                if (std::abs(xr[i]) > 1.0)
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
                        yr[i] = 0.0;
                        yi[i] = std::log(xr_i + std::sqrt(xr_i*xr_i - 1.0));
                    }
                    else if (xr_i < -1.0)
                    {
                        yr[i] = M_PI;
                        yi[i] = -std::log(std::sqrt(xr_i*xr_i - 1.0) - xr_i);
                    }
                    else
                    {
                        yr[i] = std::acos(xr_i);
                        yi[i] = 0.0;
                    }
                }
                
                return y;
            }
            else
            {
                Double* y = new Double(x->getDims(), x->getDimsArray(), false);
                
//                Map<ArrayXd> xr(x->get(), n);
//                Map<ArrayXd> yr(y->get(), n);
//                yr = xr.acos();
                
                double* xr = x->get();
                double* yr = y->get();
                
                for (int i = 0; i < n; i++)
                {
                    yr[i] = std::acos(xr[i]);
                }
                
                return y;
            }
        }
    }
    else
    {
        return Double::Empty();
    }
}

}
