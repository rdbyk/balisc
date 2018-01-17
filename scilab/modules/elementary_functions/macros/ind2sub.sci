// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA - Serge STEER
// Copyright (C) DIGITEO - 2010-2011 - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function varargout = ind2sub(dims, I)

    if nargin <> 2 then
        error(msprintf(gettext("%s: Wrong number of input argument(s): %d expected.\n"), "ind2sub", 2));
    end

    varargout = list();

    if isempty(I) then
        varargout(1) = [];
        return;
    end

    d = cumprod(double(dims));
    k1 = I;
    k = [];
    k1 = k1 - 1;

    for i = size(d, "*")-1:-1:1
        q = floor(k1/d(i));
        k1 = k1 - q * d(i);
        varargout(0) = q + 1;
    end

    varargout(0) = k1 + 1;

    if nargout == 1 then //return a matrix whose columns are the subindices
        K = []
        for k = varargout
            K = [K matrix(k, -1, 1)];
        end
        varargout = list(K);
    end

endfunction
