// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) DIGITEO - 2011 - Allan CORNET
// Copyright (C) 2012 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2013, 2018 - Samuel GOUGEON
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function i = modulo(n, m)

    if nargin <> 2 then
        error(71, 2)
    end

    mt = type(m)
    nt = type(n)
    // -----------------------  Checking arguments --------------------------

    if ~or(nt==[1 2 8]) | (nt==1 & ~isreal(n))
        error(_("%s: Wrong type for input argument #%d: Real, integer or polynomial matrix expected."), "modulo", 1)
    end

    if ~or(mt==[1 2 8]) | (mt==1 & ~isreal(m))
        error(_("%s: Wrong type for input argument #%d: Real, integer or polynomial matrix expected."), "modulo", 2)
    end

    if (nt==8 | mt==8)  & nt~=mt
        error(_("%s: Incompatible input arguments #%d and #%d: Same types expected."), "modulo", 1, 2)
    end

    // --------------------------  Processing ----------------------------

    if m==[]
        i = n;
        return
    end
    if or(mt==[1 8]) & mt==nt then
        if length(n)>1 & length(m)>1 & or(size(n) <> size(m)) then
            error(_("%s: Wrong size for input arguments: Same size expected."), "modulo")
        end
        i = n - int(n ./ m) .* m
        i = iconvert(i, inttype(n))
    else
        [i,?] = pdiv(n, m)
    end

endfunction
