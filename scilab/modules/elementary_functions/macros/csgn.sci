// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA, Serge Steer
// Copyright (C) DIGITEO - 2011 - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function s = csgn(z)
    //Kahan, W., “Branch cuts for complex elementary functions, or, Much ado about nothing's sign bit”,
    //  Proceedings of the joing IMA/SIAM conference on The State of the Art
    //  in Numerical Analysis, University of Birmingham,
    //  A. Iserles & M.J.D. Powell, eds, Clarendon Press, Oxford, 1987, 165-210.

    if nargin <> 1 then
        error(71, 1);
    end
    
    if type(z) <> [1 5] then
        error(95, 1);
    end

    s = -ones(z);
    s(real(z)>0|(real(z)==0&imag(z)>0))=1
    s(z==0) = %nan;

endfunction
