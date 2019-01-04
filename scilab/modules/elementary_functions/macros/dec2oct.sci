// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA - Pierre MARECHAL
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

function y = dec2oct(x)

    if nargin <> 1 then
        error(71, 1);
    end

    if or(type(x) <> 8) & (or(type(x) <> 1) | or(x < 0) ) then
        error(_("%s: Wrong value for input argument #%d: Scalar/vector/matrix of positive integers expected."), "dec2oct", 1);
    end

    y = dec2base(double(x), 8);

endfunction
