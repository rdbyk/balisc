// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA - Vincent COUVERT
// Copyright (C) INRIA - Pierre MARECHAL
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function mdelete(filename)

    if nargin <> 1 then
        error(77);
    end

    if type(filename) <> 10 | size(filename,"*") <> 1 then
        error(msprintf(_("%s: Wrong type for input argument: single String expected.\n"),"mdelete"));
    end

    // Handle file path
    if getos() == "Windows" then
        filename = strsubst(filename,filesep(),"/");
    end

    // File path
    k = strindex(filename,"/");

    if k == [] then
        file_path = "./";
    else
        k = k(length(k));
        file_path = part(filename,1:k);
        filename = part(filename,k+1:length(filename));
    end

    if getos() == "Windows" then
        fullfilename = strsubst(file_path+filename,"/","\");
        lst_files    = listfiles(fullfilename);
    else
        lst_files = listfiles(file_path+filename);
    end

    if lst_files <> [] then
        deletefile(lst_files);
    end

endfunction
