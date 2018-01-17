// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA - Farid BELAHCENE
// Copyright (C) 2011 - DIGITEO - Michael Baudin
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function  y=complex(varargin)

    if nargin < 1 | nargin > 2 then
        error(msprintf(gettext("%s: Wrong number of input arguments: %d to %d expected.\n"),"complex",1,2));
    end

    a = varargin(1)
    if nargin == 1 then
        b = zeros(a)
    else
        b = varargin(2)
    end

    if typeof(a) <> "constant"  then
        error(msprintf(gettext("%s: Wrong type for argument #%d: Matrix expected.\n"),"complex",1));
    end

    if typeof(b) <> "constant" then
        error(msprintf(gettext("%s: Wrong type for argument #%d: Matrix expected.\n"),"complex",2));
    end

    if size(a,"*") <> 1 & size(b,"*") <> 1 & size(a)<>size(b) then
        error(msprintf(gettext("%s: Incompatible input arguments #%d and #%d: Same sizes expected.\n"),"complex",1,2));
    end

    if ~isreal(a) then
        error(msprintf(gettext("%s: Wrong type for input argument #%d: Real matrix expected.\n"),"complex",1));
    end
    if ~isreal(b) then
        error(msprintf(gettext("%s: Wrong type for input argument #%d: Real matrix expected.\n"),"complex",2));
    end

    y = a+imult(b);

endfunction
