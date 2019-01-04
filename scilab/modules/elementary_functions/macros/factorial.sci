// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA - Farid BELAHCENE
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function y=factorial(n)

    // This function returns the factorial n. If n is a vector, matrix or hypermatrix it returns the element wise factorial
    // Input : n, a scalar/vector/matrix/hypermat of positives integers.
    // Output : y, a scalar/vector/matrix/hypermat

    if nargin <> 1 then
        error(71, 1);
    end

    if (type(n) <> 1) || (n <> [] && (or((n-floor(n) <> 0)) || or(n < 0))) then
        error(_("%s: Wrong value for input argument #%d: Scalar/vector/matrix/hypermatrix of positive integers expected."), "factorial", 1);
    elseif n == []
        y=n
        return
    else
        n(n==0)=1
        ntemp=cumprod(1:max(n))
        y=matrix(ntemp(n),size(n))
    end

endfunction
