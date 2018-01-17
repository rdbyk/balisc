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

function s = squarewave(t, percentPositive)

    if nargin < 1 then
        error(msprintf(gettext("%s: Wrong number of input argument(s): %d expected.\n"), "squarewave", 1));
    end

    if nargin < 2 then
        percentPositive=50;
    end
    s = 2*bool2s(pmodulo(t,2*%pi) < 0.02*%pi*percentPositive) - 1;

endfunction
