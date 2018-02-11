// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) DIGITEO - 2012 - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyrigth (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [m, n, nx] = %r_size(x, flag)

    if nargout == 1 then
        if nargin == 1 then
            m = size(x.num);
        else
            m = size(x.num, flag);
        end
    elseif nargout == 2 then
        if nargin <> 1 then
            error(41)
        end
        [m, n] = size(x.num);
    end

endfunction
