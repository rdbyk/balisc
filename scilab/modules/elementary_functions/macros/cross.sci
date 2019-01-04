// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Charlotte HECQUET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function c=cross(a,b)

    if nargin <> 2 then
        error(_("%s: Wrong number of input arguments: %d expected."), "cross", 2);
    end

    if type(a) > 8 | type(a) == 6 then
        error(_("%s: Wrong type for input argument #%d: A real, complex, boolean or polynomial matrix expected."), "cross", 1);
    end

    if type(b) > 8 | type(b) == 6 then
        error(_("%s: Wrong type for input argument #%d: A real, complex, boolean or polynomial matrix expected."), "cross", 2);
    end

    if size(a,1) <> size(b,1) | size(a,2)<>size(b,2) then
        error(_("%s: Wrong size for input arguments: Same sizes expected."), "cross");
    end

    if (size(a,1)<>1 | size(a,2)<>3) & size(a,1)<>3 then
        error(_("%s: Wrong size for input argument #%d: A matrix of size 1x3 or 3xN expected."), "cross", 1);
    end

    if size(a,2)==3 & size(a,1)==1 then
        c=a(:,[2 3 1]).*b(:,[3 1 2]) - a(:,[3 1 2]).*b(:,[2 3 1]);
    else
        c=a([2 3 1],:).*b([3 1 2],:) - a([3 1 2],:).*b([2 3 1],:);
    end

endfunction
