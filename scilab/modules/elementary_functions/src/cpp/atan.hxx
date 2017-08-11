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

#ifndef __ATAN_H__
#define __ATAN_H__

#include "double.hxx"

extern "C"
{
#include "dynlib_elementary_functions.h"
}

namespace balisc
{
ELEMENTARY_FUNCTIONS_IMPEXP types::Double* atan_real(types::Double* x);
ELEMENTARY_FUNCTIONS_IMPEXP types::Double* atan2(types::Double* x1, types::Double* x2);
}

#endif // __ATAN_H__
