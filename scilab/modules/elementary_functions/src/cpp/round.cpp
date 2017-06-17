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

#include "round.hxx"
#include <Eigen/Core>

using types::Double;

namespace balisc
{

Double* round(Double* x)
{
    bool is_complex = x->isComplex();
    Double* y = new Double(x->getDims(), x->getDimsArray(), is_complex);
    
    if (is_complex)
    {
        double* xr = x->get();
        double* yr = y->get();
        double* xi = x->getImg();
        double* yi = y->getImg();
        
        for (int i = 0; i < x->getSize(); i++)
        {
            yr[i] = std::round(xr[i]);
            yi[i] = std::round(xi[i]);
        }
    }
    else
    {
        double* xr = x->get();
        double* yr = y->get();
    
        for (int i = 0; i < x->getSize(); i++)
        {
            yr[i] = std::round(xr[i]);
        }
    }
    
    return y;
}

}
