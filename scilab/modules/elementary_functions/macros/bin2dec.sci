// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ???? - INRIA - Farid BELAHCENE
// Copyright (C) 2006 - INRIA - Pierre MARECHAL
// Copyright (C) 2011 - DIGITEO - Pierre MARECHAL
// Copyright (C) 2011 - DIGITEO - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function y = bin2dec(str)

    if nargin <> 1 then
        error(71, 1);
    end

    if type(str)<>10
        error(90, 1, _("matrix of strings"));
    end

    // delete all spaces included in the str
    str = strsubst(str," ","");
    y = base2dec(str, 2);

endfunction
