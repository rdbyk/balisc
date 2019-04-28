// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Antoine ELIAS
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 14055 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/14055
//
// <-- Short Description -->
// overload on matrix concatenation failed with []

function L = %l_c_s(L,N)
    L = list(L(:), N)
    assert_checkequal(N, check);
endfunction

//same function for line and column concatenation
%l_f_s = %l_c_s;

L = list("abc");

check = %pi;
l = [L check];
assert_checkequal(l($), check);
l = [L;check];
assert_checkequal(l($), check);

check = [];
l = [L check];
assert_checkequal(l($), check);
l = [L;check];
assert_checkequal(l($), check);
