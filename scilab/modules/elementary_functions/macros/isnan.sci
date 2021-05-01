// Balisc (https://github.com/rdbyk/balisc/)
//
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
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

function x = isnan(x)

    if nargin <> 1 then
        error(71, 1);
    end

	t = type(x)

	if t == 1 || t == 5 || t == 2
		x = abs(x)
		if x <> []
			if isreal(x)
				x = x <> x
			else
				x = x <> x & ~isinf(x)
			end
		end
	else
		error(90, 1, _("real, complex or polynomial matrix"));
	end

end
