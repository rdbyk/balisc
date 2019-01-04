// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2007 - INRIA - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [status,msg]=rmdir(varargin)

    select nargin
    case 0
        error(70);
        break
    case 1
        DirName = varargin(1);
        SubDirMode = %F;
        break
    case 2
        DirName = varargin(1) ;
        SubDir = convstr(varargin(2),"u");
        if (SubDir == "S") then
            SubDirMode = %T;
        else
            error(110, 2, "''s''");
        end
        break
    else
        error(70);
    end

    if SubDirMode then
        [status,msg] = hidden_rmdir(DirName);
    else
        if findfiles(DirName)<>[] then
            status = 0
            msg = _("Error: The directory is not empty.")
        else
            [status,msg] = hidden_rmdir(DirName);
        end
    end

endfunction

function [status,msg]=hidden_rmdir(DirName)

    if isdir(DirName) then
        bOK = removedir(DirName);
        if bOK then
            msg = "";
            status = 1;
        else
            msg = msprintf(_("%s: An error occurred: %s\n"),"rmdir", _("Undefined"));
            status = 0;
        end
    else
        msg = msprintf(_("%s: An error occurred: %s\n"),"rmdir", _("The system cannot find the file specified."));
        status = 0;
    end

endfunction
