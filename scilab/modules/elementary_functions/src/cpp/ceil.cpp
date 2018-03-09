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

#include "ceil.hxx"
#include <Eigen/Core>

using types::Double;

using Eigen::Map;
using Eigen::ArrayXd;

namespace balisc
{

Double* ceil(Double* x)
{
    bool is_complex = x->isComplex();
    Double* y = x->getRef() > 1 ? new Double(x->getDims(), x->getDimsArray(), is_complex) : x;

    int n = x->getSize();
    
    Map<ArrayXd> xr(x->get(), n);
    Map<ArrayXd> yr(y->get(), n);
    yr = xr.ceil();
                
    if (is_complex)
    {
        Map<ArrayXd> xi(x->getImg(), n);
        Map<ArrayXd> yi(y->getImg(), n);
        yi = xi.ceil();
    }
    
    return y;
}

}
