// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA -
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.


function r=%i_j_s(a,n)
    if or(int(n)<>n)|or(n<0) then
        r=double(a).^n
    else
        if size(a,"*")==1 then
            r=iconvert(double(a).^n,inttype(a))
        else
            if size(n,"*")<>1 then
                error(24)
            else
                r=a
                for i=2:n,r=r.*a,end
            end
        end
    end
endfunction
