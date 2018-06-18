// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 1989 - INRIA - Serge Steer
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function titlepage(str,win)
    //titlepage(str) genere une page de titres graphiques contenant la ma-
    //trice de chaines de caracteres str ecrite centree dans  la page avec
    //une taille de caractere maximale.
    //!

    if ~isdef("str") then
        msg = _("%s: Wrong number of input arguments: %d or %d expected.\n")
        error(msprintf(msg, "titlepage", 1, 2));
    end

    if type(str) <> 10 then
        msg = _("%s: Wrong type for input argument #%d: String array expected.\n")
        error(msprintf(msg, "titlepage", 1));
    end


    old = gcf()
    if nargin==2 then
        scf(win)
    end
    plot2d([0,1],[0,1],[-1,-1],"022");
    xstringb(0,0,str,1,1,"fill");
    scf(old)
endfunction
