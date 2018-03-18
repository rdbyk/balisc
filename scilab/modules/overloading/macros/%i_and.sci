// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ???? - INRIA
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function x=%i_and(a,flag)
    // or(a) returns the logical OR
    // for scalar matrices, an entry is TRUE if it is not zero.
    //!
    if nargin==1 || flag=="*" then
        x=find(a==0,1)==[]
    else
        x=sum(bool2s(a<>0),flag)==size(a,flag)
    end
endfunction
