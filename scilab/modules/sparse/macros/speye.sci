// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [sp]=speye(m,n)

    if nargin == 1 then
        [m,n] = size(m)
    end

    mn = min(m,n)

    if mn < 1 then
        sp=sparse([],[])
    else
        sp=sparse([(1:mn)' (1:mn)'],ones(mn,1),[m,n])
    end

endfunction
