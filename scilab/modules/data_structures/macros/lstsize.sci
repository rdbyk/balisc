// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - Scilab Enterprises - Antoine ELIAS
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function l = lstsize(varargin)
    warnobsolete("size()","6.1");
    if nargout <> 1 then
        error(msprintf(_("%s: Wrong number of output arguments: %d expected.\n"), "lstsize", 1));
    end

    if nargin <> 1 then
        error(msprintf(_("%s: Wrong number of input arguments: %d expected.\n"), "lstsize", 1));
    end


    var = varargin(1);
    if type(var) <> 15 & type(var) <> 16 & type(var) <> 17 then
        error(msprintf(_("%s: Wrong type for argument %d: List expected.\n"), "lstsize", 1));
    end

    l = size(var);
endfunction
