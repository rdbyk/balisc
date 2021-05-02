// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - DIGITEO - Sylvestre LEDRU
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 426 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=426
//
// <-- Short Description -->
// Wrong permutation

a = ['aaa';'eee';'ccc';'bbb';'ddd';'rrr'];
trueValue=[1; 4; 3; 5; 2; 6];

[b result] = gsort(a,'r','i')
assert_checkequal(result, trueValue);
