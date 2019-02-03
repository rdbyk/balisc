// Balisc (https://github.com/rdbyk/balisc/)
//
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
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

function y=trace(u)

    if nargin < 1 then
        error(71, 1);
    end

    if type(u)<>[1:8,16,17] then
        error(msprintf(gettext("%s: Wrong type for input argument #%d.\n"),"trace",1));
    end

    if ~issquare(u) then
        error(103, 1);
    end

    y = sum(diag(u));

endfunction
