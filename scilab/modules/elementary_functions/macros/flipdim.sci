// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA - Farid BELAHCENE
// Copyright (C) DIGITEO - 2011 - Allan CORNET
// Copyright (C) 2013, 2019 Samuel GOUGEON
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function y = flipdim(x, dim, sb)

    if nargin < 2 then
        error(72, 2, 3);
    end

    if size(dim, "*") <> 1 then
        msg = _("%s: Wrong size for input argument #%d: A scalar expected.\n")
        error(msprintf(msg, "flipdim", 2));
    elseif type(dim) <> 8 && (type(dim) <> 1 || dim < 1 ) then
        msg = _("%s: Wrong type for input argument #%d: A positive integer expected.\n");
        error(msprintf(msg, "flipdim", 2));
    elseif dim > ndims(x) then
        msg = _("%s: Argument #%d: Must be <= %d.\n");
        error(msprintf(msg, "flipdim", 3, ndims(x)));
    else
        dim = floor(dim);
    end
    if nargin >= 3 then
        if size(sb, "*") <> 1 then
            msg = _("%s: Wrong size for input argument #%d: A scalar expected.\n")
            error(msprintf(msg, "flipdim", 3));
        elseif and(type(sb) <> [1 8]) || sb < 1 then
            msg = _("%s: Wrong value for input argument #%d: A positive integer expected.\n");
            error(msprintf(msg, "flipdim", 3));
        elseif modulo(size(x, dim), sb) ~= 0 then
            msg = _("%s: Wrong value for input argument #%d: A divisor of the selected dimension size expected.\n");
            error(msprintf(msg, "flipdim", 3));
        end
    end

    l = list();
    for k = 1:ndims(x)
        l(k) = 1:1:$
    end
    if nargin>2 then
        sb  = floor(sb);
        nb = size(x, dim)/sb; // Number of blocks.
        l(dim) = ((nb:-1:1).*.ones(1,sb))*sb + ones(1, nb).*.(1-sb:0);
    else
        l(dim) = $:-1:1
    end
    y = x(l(:));
endfunction
