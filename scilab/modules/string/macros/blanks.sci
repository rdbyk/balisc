// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

// blanks macro
// blanks(n)
// Create string of blank characters

function str = blanks(n)

    if ~or(type(n)==[1,8]) then
        error(92, 1);
    end

    if size(n,"*") <> 1 then
        error(101, 1);
    end

    if n<0 then
        error(110, 1, _("non-negative integer value"));
    else
        str = part(" ",ones(1,n));
    end

endfunction
