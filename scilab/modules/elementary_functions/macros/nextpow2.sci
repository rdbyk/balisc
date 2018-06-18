// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) DIGITEO - 2011 - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function e = nextpow2(n)

    if nargin <> 1 then
        error(msprintf(gettext("%s: Wrong number of input arguments: %d expected.\n"),"nextpow2", 1));
    end

    n = abs(n);
    kf = find(~isnan(n) & n<>%inf);
    e = n;
    f = zeros(n);
    [f(kf), e(kf)] = frexp(n(kf));
    k = find(f==0.5); // n(k) is a power of 2

    if k <> []
        e(k) = e(k)-1;
    end

endfunction
