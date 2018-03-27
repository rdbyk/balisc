// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2010 - DIGITEO - Antoine ELIAS
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.


function l = lstcat(varargin)
    // concat inputs in a list

    l = list();

    if nargin==0 then
        return;
    end

    for i=1:nargin
        var = varargin(i);
        if type(var) == 15 then
            for j = 1 : size(var)
                l($ + 1) = var(j);
            end
        elseif type(var) <= 10 then
            l($ + 1) = var;
        end
    end
endfunction
