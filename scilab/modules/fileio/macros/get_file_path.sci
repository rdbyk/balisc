// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function path = get_file_path(name)
    //-------------------------------
    // returns loader full path

    path ="./";
    [units,types,names]=file();

    for k=size(names,"*"):-1:1
        l=strindex(names(k),name);
        if l<>[] then
            path=part(names(k),1:l(length(l))-1);
            break
        end
    end

    if path == "" then
        path = pwd()
    end

endfunction
