// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA, Serge Steer
// Copyright (C) 2010 - DIGITEO - Michael Baudin
// Copyright (C) DIGITEO - 2011 - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
// Copyright (C) 2019 - Samuel GOUGEON
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function y = tand(x)

    if nargin <> 1 then
        error(71, 1);
    end

    if ~or(type(x)==[1 5]) | ~isreal(x) then
		error(94, 1);
    end

    if x <> []
		m = pmodulo(x, 360);
        n = round(x / 180);
        x = x - n * 180;
        y = tan(%pi/180*x);
        y(m == 90) = %inf;
        y(m == 270) = -%inf;
    else
        y = []
    end

endfunction
