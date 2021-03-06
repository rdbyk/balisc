// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2007 - INRIA - Allan CORNET
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

function files= listfiles(paths,flag,flagexpand)

    if nargin < 1  then
        paths="./"
    end

    if nargin <= 1 then
        flag = %t
    end

    if nargin <= 2 then
        flagexpand = %t
    end

    files=[];

    paths = stripblanks(paths);

    // list files of the current directory
    paths(find(paths=="")) = "./";

    if flag == %t then
        paths = pathconvert(paths,%f,flagexpand);
    end

    // list files of the root directory
    if getos() <> "Windows" then
        paths(find(paths=="")) = "/";
    end

    DIR_SEPARATOR=filesep();

    bMulti = %f;
    if size(paths,"*") > 1 then
        bMulti = %t;
    end

    for i=1:size(paths,"*")  // Loop on the file/path list
        if isdir(paths(i)) then // It is a directory then returns all the file in the dir
            path = paths(i) + filesep();
            fname = "*";
            extension = "";
        else //isfile
            [path, fname, extension] = fileparts(paths(i)); // Retrieve the information
            if path == "" then
                path = "./";
            end
            
            if fname == "" then
                fname = "*";
            end
        end

        filesi=findfiles(path,fname+extension);

        if filesi<>[] then
            filesi=filesi($:-1:1);
            // prepend with the path, if required
            // when listing a full directory, path is not prepended
            dirs=paths(i);
            if part(dirs,length(dirs))<>DIR_SEPARATOR then
                if isdir(dirs) then
                    if bMulti then //yes
                        with_dir=%t;
                        dirs = dirs + filesep();
                    else
                        with_dir=%f;
                    end
                else                //no
                    k=strindex(dirs,DIR_SEPARATOR);
                    if k==[] then
                        with_dir=%f;
                    else
                        dirs=part(dirs,1:k(length(k)));
                        with_dir=%t;
                    end
                end
            else
                with_dir=%f;
            end // if part(dirs,length(dirs) ...

            if with_dir then
                filesi = dirs+filesi;
            end

            files=[files;filesi];
        end // if filesi<>[] then
    end // for i=1:size(paths,'*')
endfunction
