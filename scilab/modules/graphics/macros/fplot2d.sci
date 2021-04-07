// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function []=fplot2d(xr,f,style,strf,leg,rect,nax,dummy)
    // 2D plot of function f : a Scilab function or the name (as a string)
    //  of a dynamically linked function.
    // Enter fplot2d() for an example.
    // deff('<y>=f(x)','y=sin(x)+cos(x)');
    // fplot2d(f,0:0.1:%pi);
    //!

    if nargin <= 0 then   // demo
        deff("[y]=f(x)","y=sin(x)+cos(x)");
        fplot2d(0:0.1:%pi,f);
        return
    end

    if type(xr)=="10" then // logflag passed first
        error(msprintf(gettext("%s: Wrong size for input argument #%d: A vector expected.\n"), "fplot2d", 1));
    elseif nargin < 2 then
        error(msprintf(gettext("%s: Wrong number of input arguments: At least %d expected.\n"), "fplot2d", 2));
    end
    //handling optional arguments

    opts=[]

    if ~isvoid(style) then opts=[opts,"style=style"],end
    if ~isvoid(strf) then opts=[opts,"strf=strf"],end
    if ~isvoid(leg) then opts=[opts,"leg=leg"],end
    if ~isvoid(rect) then opts=[opts,"rect=rect"],end
    if ~isvoid(nax) then opts=[opts,"nax=nax"],end
    if exists("logflag","local")==1 then opts=[opts,"logflag=logflag"],end
    if exists("frameflag","local")==1 then opts=[opts,"frameflag=frameflag"],end
    if exists("axesflag","local")==1 then opts=[opts,"axesflag=axesflag"],end
    if size(opts,2)<nargin-2 then
        error(msprintf(gettext("%s: Wrong value for input argument: ''%s'', ''%s'', ''%s'', ''%s'', ''%s'', ''%s'', ''%s'' or ''%s'' expected.\n"),"fplot2d","style","strf","leg","rect","nax","logflag","frameflag","axesflag"));
    end

    if isempty(opts) then
        plot2d(xr,feval(xr,f))
    else
        execstr("plot2d(xr,feval(xr,f),"+strcat(opts,",")+")")
    end

endfunction
