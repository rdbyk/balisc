// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Samuel Gougeon
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function r = isrow(v)

    if nargin <> 1 then
        error(msprintf(gettext("%s: Wrong number of input arguments: %d expected.\n"),"isrow", 1));
    end

    s = size(v)
    s2 = s(find(s(2:length(s))>=1))
    r = s(1)==1 & (length(s2)==1 | prod(s2)==1)

endfunction
