// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Sylvestre Koumar
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function myTree = uiCreateTree(parentNode, varargin)

    //Input arguments checking
    if nargin == 0 then
        error(msprintf(gettext("%s: Wrong number of input arguments: At least %d expected.\n"), "uiCreateTree",1));
        return;
    end

    if nargin >=1 then
        // Check if parentNode is a Tree
        if (typeof(parentNode) == "uitree") then
            myTree = tlist("uitree", parentNode(2));
            // Add subTrees into myTree
            for subTreesIndex = 1:size(varargin)
                if (typeof(varargin(subTreesIndex)) == "uitree") then
                    myTree(subTreesIndex + 2) = varargin(subTreesIndex)
                else
                    error(msprintf(gettext("%s: Wrong type for element %d of input argument #%d: uitree expected.\n"), "uiCreateTree", subTreesIndex, 2));
                    return;
                end
            end
        else
            error(msprintf(gettext("%s: Wrong type for input argument #%d: uitree expected.\n"), "uiCreateTree",1));
            return;
        end
    end

endfunction
