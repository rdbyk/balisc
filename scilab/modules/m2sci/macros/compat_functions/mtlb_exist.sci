// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2002-2004 - INRIA - Vincent COUVERT
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function r=mtlb_exist(nam,wh)
    // Emulation function for exist() Matlab function

    if isdef(nam) && typeof(evstr(nam)) == "fptr" then
        fptr = nam
    else
        fptr = 0
    end

    r=0
    if nargin==1 then
        if fptr<>0 then
            fptr=int(fptr/1000)
            if fptr<=500 then
                r=5
            else
                r=3
            end
        elseif exists(nam)==1 then
            if type(nam)==13 then
                r=2
            else
                r=1
            end
        end
    else
        select wh
        case "var" then
            if exists(nam)==1 then r=1,end
        case "builtin" then
            if fptr<>0 then
                fptr=int(fptr/1000)
                if fptr<=500 then
                    r=5
                else
                    r=3
                end
            end
        case "file" then
        case "dir" then
        end
    end
endfunction
