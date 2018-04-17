// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ENPC - JPC
// Copyright (C) INRIA - Serge Steer , Francois Delebecque
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function   [den,num,err]=arl2(y,den0,n,imp,all)
    // test the system type 'c' 'd' or dt
    if nargin <= 4 then all="one";end
    if nargin <= 3 then imp=0;end
    if all=="all" then
        [den,num,err]=arl2_ius(y,den0,n,imp,all);
    else
        [den,num,err]=arl2_ius(y,den0,n,imp);
    end;
    if nargout<=1 then
        den=syslin("d",num,den);
    end
endfunction
