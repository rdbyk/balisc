// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013, 2016 - Samuel GOUGEON
// Copyright (C) 2018 - Stéphane MOTTELET
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function y = %r_permute(x, dims)

    // This function returns an array y which results of the x permutation
    // Input :
    // -x a (multi-dimensionnnal) array of rationals
    // -dims a vector which contains the permutation order
    // Output :
    // -y the result of the x permutation
    // History:
    // 2013 - S. GOUGEON  : processing rewritten, fixing http://bugzilla.scilab.org/5205
    // 2016 - S. GOUGEON  : extension to rationals
    // 2018 - S. MOTTELET : restrict to rationals as permute() is now a native function

    // CHECKING ARGUMENTS
    // ------------------
    if nargin <> 2 then
        error(71, 2);
    end

    // Verify if the size of dims corresponds to dimension of x
    if ~(or(type(dims)==[1 8]) && and(int(dims)==dims) && ..
        and(gsort(dims(:)',"g","i")==(1:max(length(dims),ndims(x))))) then
        error(_("%s: Wrong value for input argument #%d: Must be a valid permutation of [1..n>%d] integers."), "permute", 2, ndims(x)-1);
    end

    y=x;
    y.num=permute(x.num, dims);
    y.den=permute(x.den, dims);

endfunction
