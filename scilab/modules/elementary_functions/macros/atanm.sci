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

function x=atanm(a)

    if nargin <> 1 then
        error(71, 1);
    end

    if type(a)<>1 then
        error(95, 1);
    end

    if ~issquare(a) then
        error(103, 1);
    end

    //diagonalization
    [x,t,bs]=bdiag(a+0*%i*ones(a),1/%eps);

    if find(bs>1)<>[] then
        error(_("%s: Matrix is not diagonalisable."), "atanm");
    end

    x=t*diag(atan(diag(x)))/t;

    if isreal(a,0) then
        x=real(x)
    end

endfunction
