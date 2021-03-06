// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) Samuel GOUGEON - 2015-2016 - sgougeon@free.fr : Bug 13893
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyrigth (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function h = %r_simp(h, d)
    // implement complex case
    // 0/den => 0/1
    
    if nargin==1 then
        n = h.num
        d = h.den
    else
        n = h
        h = []
    end

    i = find(clean(n)==0 & clean(d)~=0)
    [n, d] = simp(n, d);
    d(i) = 1
    h = rlist(n, d, h(4))

endfunction
