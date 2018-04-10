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

function []=xload(fil,num)

    if and(nargin<>[1 2]) then
        error(msprintf(gettext("%s: Wrong number of input argument(s): %d or %d expected.\n"), "xload", 1, 2));
    end

    if ~isfile(fil) then
        error(msprintf(gettext("%s: file %s does not exist.\n"), "xload", fil));
    end

    if  nargin==2 then scf(num),end
    %__f__=gcf();
    res = execstr("load(fil)","errcatch") ;
    // Get latest figure created by load
    loadedFig = gcf();
    for kC=1:size(loadedFig.children, "*")
        copy(loadedFig.children(kC), %__f__); // Copy axes
    end
    delete(%__f__.children($));
    delete(loadedFig); // Delete it, returned figure will be the one set as current by xload
    if res==0 then
        %__f__.visible="on"
        %__f__.immediate_drawing="on";
    else
        error("Given file is not a graphic one") ;
    end

endfunction
