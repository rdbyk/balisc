// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ENPC
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [files]= dirname(files,flag,flagexpand)

    if nargin <= 1 then
        flag = %t
    end

    if nargin <= 2 then
        flagexpand = %t
    end

    if flag == %t then
        files = pathconvert(files,%f,flagexpand);
    end

    sep = filesep();

    for i=1:size(files,"*")
        fname = files(i)
        k = strindex(fname,sep);
        if k <> [] then
            fname = part(fname,1:k(length(k))-1);
        else
            fname = "."; //emptystr();
        end
        files(i)= fname;
    end

endfunction
