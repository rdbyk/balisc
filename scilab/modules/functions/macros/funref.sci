// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
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

// FIXME: (re)implement it using C++  

function r = funref(name)

    if nargin <> 1
        error(71, 1)
    end

    if type(name) <> 10
        error(91)
    end

    if size(name,'*') <> 1
        error(102)
    end
    
    if isdef(name)
        execstr("r="+name);
        if type(r) <> [13 130]
            r = []
        end
    else
        r = []
    end

end
