// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2007 - INRIA - Pierre MARECHAL
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function status = is_absolute_path(pathname)

    pathname = stripblanks(pathname,%T);

    if getos() == "Windows" then

        status = %F;

        if isletter(part(pathname,1)) & (part(pathname,2) == ":") then
            status = %T;
        end

        if (part(pathname,[1:7])=="file:")   ..
            | (part(pathname,[1:2])=="\\")   ..
            | (part(pathname,[1:2])=="//") then
            status = %T;
        end

    else
        first = part(pathname,1)
        status = first == "/" | first == "~";
    end

endfunction
