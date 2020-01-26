// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2002-2004 - INRIA - Vincent COUVERT
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function val=mtlb_realmin(prec)
    // Emulation function for Matlab realmin()

    if nargin<=0 then
        val=number_properties("tiny");
    elseif nargin==1 then
        if prec=="double" then
            val=number_properties("tiny");
        else
            error(msprintf(gettext("%s: Not yet implemented.\n"),"mtlb_realmin"));
        end
    else
        error(msprintf(gettext("%s: Wrong number of input arguments: %d to %d expected.\n"),"mtlb_realmin",0,1));
    end
endfunction
