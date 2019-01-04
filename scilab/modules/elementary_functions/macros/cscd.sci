// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA, Serge Steer
// Copyright (C) - 2010 - DIGITEO - Michael Baudin
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

function x = cscd(x)

    if nargin <> 1 then
        error(71, 1);
    end

    if type(x) <> 1 || ~isreal(x) then
        error(94, 1);
    end

    if x <> []
        n = round(x/90);
        x = %pi/180 * (x - n*90);
        m = pmodulo(n,4);
        x(m==0) = 1 ./ sin(x(m==0));
        x(m==1) = 1 ./ cos(x(m==1));
        x(m==2) = -1 ./ sin(x(m==2));
        x(m==3) = -1 ./ cos(x(m==3));
    end

endfunction
