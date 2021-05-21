// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Samuel GOUGEON
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function x = fftshift(x, along)

    way = "ceil"
    if ~isdef("ifftshift_way","n") then
        fname = "fftshift"
    else
        fname = "ifftshift"
        way = "floor"
    end
    if nargin < 1 | nargin > 2 then
        error(73, 1, 2);
    end

    // Checking "along"
    if nargin < 2 then
        along = "all"
    end
    if along=="r" then
        along = 1
    elseif along=="c" then
        along = 2
    end
    if and(type(along)~=[1 8 10]) | (type(along)==10 & along~="all")|..
      (type(along)==1 & (~isreal(along) | along<1 |  along > ndims(x))) then
        msg = _("%s: Argument #%d: Must be in the set {%s}.\n");
        Set = strcat(msprintf("%d\n", (1:ndims(x))'),",")
        error(msprintf(msg, fname, 2, Set))
    end

    // PROCESSING
    // ----------
    deff("sel=fun(sk)", "c=" + way + "(sk/2); sel=[c+1:sk,1:c]")
    ind = list()
    if along=="all" then
        for sk = size(x)
            ind($+1) = fun(sk)
        end
    else
        for sk = size(x)
            ind($+1) = 1:$;
        end
        ind(along) = fun(size(x, along))
    end
    x = x(ind(:))
endfunction
