// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA, Serge Steer
// Copyright (C) 2010 - DIGITEO - Michael Baudin
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

function y = tand(x)

    if nargin <> 1 then
        error(msprintf(gettext("%s: Wrong number of input arguments: %d expected.\n"),"tand", 1));
    end

    if type(x)<>1 || ~isreal(x) then
        error(msprintf(gettext("%s: Wrong type for input argument #%d: Real matrix expected.\n"),"tand",1));
    end

    // Argument reduction toward [-90,90[
    if x <> []
        n = round(x / 180);
        y = tan(%pi/180* (x - n * 180));
        // Set all singular points to nan
        m = pmodulo(x + 90, 180);
        y(m == 0) = %nan;
    else
        y = []
    end

endfunction
