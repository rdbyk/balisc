// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA, Serge Steer
// Copyright (C) - 2010 - DIGITEO - Michael Baudin
// Copyright (C) DIGITEO - 2011 - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
// Copyright (C) 2019 - Samuel GOUGEON
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function x = cosd(x)

    if nargin <> 1 then
        error(71, 1);
    end

    if ~or(type(x)==[1 5]) | ~isreal(x) then
		error(94, 1);
    end

    if x <> []
        x = x - round(x/360)*360;
        y = cos(%pi/180*x);
        y(x==-90|x==90) = 0; 
        x = y;
    end

endfunction
