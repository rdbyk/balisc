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

function []=mtlb_box(axes_handle,val)
    // Emulation function for Matlab box()

    a=gca();

    if nargin<=0 then // box toggle
        if a.box=="on" then
            a.box="off"
        else
            a.box="on"
        end
    elseif nargin==1 then
        if type(axes_handle)==10 then // box on/off
            a.box=convstr(axes_handle,"l")
        else // box(axes_handle)
            if axes_handle.box=="on" then
                axes_handle.box="off"
            else
                axes_handle.box="on"
            end
        end
    elseif nargin==2 then // box(axes_handle,...)
        axes_handle.box=convstr(val,"l")
    else
        error(msprintf(gettext("%s: This feature has not been implemented.\n"),"mtlb_box"));
    end

endfunction
