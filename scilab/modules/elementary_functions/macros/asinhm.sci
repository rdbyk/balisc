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

function t=asinhm(x)
    // Matrix wise Hyperbolic sine inverse of x
    // Entries of x must be in ]-1,i[
    // Entries of t are in    ]-inf,inf[ x ]-pi/2,pi/2[
    //                             ]-inf, 0 ] x [-pi/2]
    //                      and    [ 0  ,inf[ x [ pi/2]

    if nargin <> 1 then
        error(71, 1);
    end

    if type(x)<>1 then
        error(95, 1);
    end

    if ~issquare(x) then
        error(103, 1);
    end

    t=logm(x+sqrtm(x*x+eye()));

endfunction
