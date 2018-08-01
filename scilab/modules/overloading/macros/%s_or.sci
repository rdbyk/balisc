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

function x = %s_or(a,flag)
    // or(a) returns the logical OR between a's components.
    // A component is TRUE if it is not zero (including %nan)
    //!

    if nargin==1 then flag="*",end

    if flag=="*" then
        if a==[]
            x = %f
        else
            x = find(a<>0,1)<>[]
        end
    else
        if a==[] then
            x = []
        else
            x = sum(bool2s(a),flag)>=1
        end
    end

endfunction
