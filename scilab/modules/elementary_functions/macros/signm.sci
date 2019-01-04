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

function x = signm(a)

    if nargin <> 1 then
        error(71, 1);
    end

    [m, n] = size(a);

    if m <> n then
        error(103, 1);
    end

    if or(a <> a') then
        error(110, 1, _("hermitian matrix"));
    end

    [u, s] = schur(a);
    x = u'*diag(sign(real(diag(s)))) * u;

endfunction
