// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) DIGITEO - 2011 - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [x,ka,kb] = union(a, b, orient)
    // returns the union of  unique components of  vector a and b
    // author Serge Steer INRIA

    if nargin < 2 then
        error(msprintf(gettext("%s: Wrong number of input arguments: %d expected.\n"), "union", 2));
    end

    if nargin < 3 then
        if nargout==1 then
            x=unique([a(:);b(:)])
            x=x';
        else
            kab=[1:size(a,"*"), -(1:size(b,"*"))]
            [x,k]=unique([a(:);b(:)])
            x=x'
            kab=kab(k)
            ka=kab(kab>0)
            kb=-kab(kab<0)
        end
    else
        if  orient==1|orient=="r" then
            if nargout==1 then
                x=unique([a;b],"r")
            else
                kab=[1:size(a,"r"), -(1:size(b,"r"))]
                [x,k]=unique([a;b],"r")
                kab=kab(k)
                ka=kab(kab>0)
                kb=-kab(kab<0)
            end
        elseif orient==2|orient=="c" then
            if nargout==1 then
                x=unique([a b],"c")
            else
                kab=[1:size(a,"c"), -(1:size(b,"c"))]
                [x,k]=unique([a b],"c")
                kab=kab(k)
                ka=kab(kab>0)
                kb=-kab(kab<0)
            end

        else
            error(msprintf(gettext("%s: Wrong value for input argument #%d: %d,''%s'',%d or ''%s'' expected\n"),"unique",3,1,"r",2,"c"));
        end
    end
endfunction
