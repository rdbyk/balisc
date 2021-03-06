// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA
// Copyright (C) 2012- Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function c = cond(varargin)

    select nargin
    case 1
        // c=cond(A) condition number for 2-norm
        // cond(A) is the ratio of the largest singular of x to the smallest
        // Warning: the svd function doesn't manage sparse matrices
        A = varargin(1);
        if type(A) == 1 then
            if or(isnan(A)) | or (isinf(A)) then
                error(_("%s: Wrong value for input argument #%d: must not contain %s or %s."), "cond", 1, "%nan", "%inf");
            end
            if A == [] then
                c = 0;
                return
            end
            s = svd(A);
            if s($) == 0 then
                c = %inf;
            else
                c = s(1)/s($);
            end
        else
            error(_("%s: Wrong type for input argument #%d: A matrix expected."), "cond", 1);
        end
    case 2
        // c = cond(A, p) where p = 1, %inf, fro, ..
        // norm(A, p) * norm(inv(A), p)
        // Warning inv doesn't manage no square and sparse matrices
        A = varargin(1);
        p = varargin(2);
        [m,n] = size(A);
        if type(A) <> 1 | m <> n then
            error(_("%s: Wrong type for input argument #%d: A square matrix expected."),"cond", 1);
        end
        if and(type(p) <> [1, 10]) then
            error(_("%s: Wrong type for input argument #%d: A scalar or a string expected."),"cond", 2);
        end
        if and(p <> [1 2 %inf] & p <> ["inf","fro"]) then
            error(_("%s: Wrong value for input argument #%d: must be %d, %d, %s, ''%s'' or ''%s''."), "cond", 2, 1, 2, "%inf", "inf", "fro");
        end

        c = norm(A, p) * norm(inv(A), p);
    else
        error(_("%s: Wrong number of input arguments: %d to %d expected.\n"), "cond", 1, 2);
    end

endfunction
