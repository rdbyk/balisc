// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2005 - INRIA - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [] = wavwrite(y,Fs,nbits,wavefile)

    Fs_pref = 22050;
    nbits_pref = 16;

    // Parse inputs:
    if  nargin < 2 | nargin > 4 then
        error(msprintf(gettext("%s: Wrong number of input arguments: %d to %d expected.\n"),"wavwrite",2,3));
    elseif nargin < 3 then
        wavefile = Fs;
        Fs = Fs_pref;
        nbits = nbits_pref;
    elseif nargin < 4 then
        wavefile = nbits;
        nbits = nbits_pref;
    end

    savewave(wavefile,y,Fs,nbits);

endfunction
