// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) DIGITEO - 2011 - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [f, e] = log2(x)
    // x may be positive, negative, or complex
    if nargin <> 1 then
        error(71, 1)
    end

    if nargout <= 1 then
        // 1/log(2) = 1.4426950408889633870047
        f = log(x) * 1.4426950408889633870047
    else
        [f, e] = frexp(x)
    end

endfunction
