// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2007 - INRIA - Allan CORNET
// Copyright (C) 2010 - DIGITEO - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [status, msg]=mkdir(varargin)

    DirName = "";
    NewDirName = "";
    status = 0 ;
    msg = "";

    select nargin

    case 0
        error(70);
        break

    case 1
        NewDirName = varargin(1);
        if type(NewDirName) <> 10 then
            error(91, 1);
        end

        if size(NewDirName, "*") <> 1 then
            error(102, 1);
        end

        NewDirName = stripblanks(NewDirName, %T);
        if is_absolute_path(NewDirName) then
            NewDirectory = NewDirName;
        else
            NewDirectory = fullfile(pwd(),NewDirName);
        end
        break

    case 2
        DirName  = varargin(1);
        if type(DirName) <> 10 then
            error(91, 1);
        end

        if size(DirName, "*") <> 1 then
            error(102, 1);
        end

        NewDirName   = varargin(2);
        if type(NewDirName) <> 10 then
            error(91, 2);
        end

        if size(NewDirName, "*") <> 1 then
            error(102, 2);
        end

        NewDirName = stripblanks(NewDirName, %T);
        DirName = stripblanks(DirName, %T);
        NewDirectory = fullfile(DirName, NewDirName);
        break

    else
        error(70);
    end

    NewDirectory = fullpath(NewDirectory);

    if isdir(NewDirectory) then
        // it is a directory
        status = 2;
    elseif isfile(NewDirectory) then
        // it is a file
        status = -2;
    else
        // The directory does not exist
        status = 1;
    end

    select status

    case 0
        break

    case 1
        bAddFirstDirSep = %f;
        subdirs = strsplit(NewDirectory, ["/" "\"]);
        if subdirs(1) == "" then
            subdirs(1) = [];
            bAddFirstDirSep = %t;
        end
        for i = 1:size(subdirs, "*")
            currentsubdir = strcat(subdirs(1:i), filesep());
            if bAddFirstDirSep then
                currentsubdir = filesep() + currentsubdir;
            end
            if ~(isfile(currentsubdir) || isdir(currentsubdir)) then
                status = createdir(currentsubdir);
                if ~status then
                    break
                end
            end
        end

        if ~(isdir(NewDirectory) || isfile(NewDirectory)) then
            status = createdir(NewDirectory);
        end

        if (status) then
            msg = "";
            status = 1;
        else
            msg = msprintf(_("%s: An error occurred: %s\n"),"mkdir",_("Impossible to create directory ")) + NewDirectory;
            status = 0;
        end
        break

    case 2
        msg = msprintf(_("%s: An error occurred: %s\n"),"mkdir",_("This directory already exists in ")) + NewDirectory;
        break

    case -2
        msg = msprintf(_("%s: An error occurred: %s\n"),"mkdir",_("A file with the same name already exists in ")) + DirName;
        break

    else
        msg = msprintf(_("%s: An error occurred: %s\n"),"mkdir",_("Impossible to create directory ")) + NewDirectory;
    end

endfunction
