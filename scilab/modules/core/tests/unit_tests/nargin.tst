// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Charlotte HECQUET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
//
// <-- Short Description -->
// Unit test for nargin

function res = test(a,b, varargin)
    if nargin > 4 then
        error(msprintf(gettext("%s: Wrong number of input arguments: %d to %d expected.\n"), "test", 1, 4));
    end
    res = nargin;
endfunction

assert_checkequal(test(1), 1);
assert_checkequal(test(1,2), 2);
assert_checkequal(test(1,2, 3), 3);
assert_checkequal(test(1,2,3,4), 4);
errmsg = msprintf(gettext("%s: Wrong number of input arguments: %d to %d expected.\n"), "test", 1, 4);
assert_checkerror("test(1,2,3,4,5)", errmsg);
