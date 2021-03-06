// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Raise Partner - Mohamed Houacine: fixed bug #13116
// Copyright (C) INRIA - Serge Steer
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [x, iact, iter, f]=qpsolve(Q,p,C,b,ci,cs,me)

    if nargin <> 7
        error(msprintf(gettext("%s: Wrong number of input arguments: %d expected.\n"), "qpsolve", 7));
    end
    C(me+1:$, :) = -C(me+1:$, :);
    b(me+1:$) = -b(me+1:$);
    // replace boundary constraints by linear constraints
    Cb = []; bb = [];
    if ci <> [] then
        Cb = [Cb; speye(Q)]
        bb = [bb; ci]
    end
    if cs <> [] then
        Cb = [Cb; -speye(Q)]
        bb = [bb; -cs]
    end
    C = [C; Cb]; b = [b; bb]
    [x, iact, iter, f] = qp_solve(Q, -p, C', b, me)

endfunction
