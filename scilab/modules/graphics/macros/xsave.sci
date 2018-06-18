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

function xsave(fil,num)
    if nargin<1 then
        error(msprintf(gettext("%s: Wrong number of input arguments: At least %d expected.\n"), "xsave", 1));
    end
    if nargin<2 then
        f=gcf()
        preservecur=%f
    else
        preservecur=winsid()<>[]
        if preservecur then old=gcf();end
        f=scf(num);
    end
    save(fil,"f")
    if preservecur then scf(old),end
endfunction
