// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyrigth (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [m,n,nx]=%lss_size(x,flag)

    [b,c,d]=x(3:5);
    m=size([c,d],1);
    n=size([b;d],2);

    if nargin==2 then
        if type(flag)==10 then
            if part(flag,1)=="r" then
                flag=1;
            elseif part(flag,1)=="c" then
                flag=2;
            end
        end
    end

    select nargout
        case 1
            if nargin==1 then
                m=[m,n]
            elseif flag==1
                m=m
            elseif flag==2
                m=n
            elseif flag=="*" then
                m=m*n
            end
        case 2 then
            return
        case 3 then
            [nx,nx]=size(x(2))
    end

endfunction
