// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2017 - Samuel GOUGEON
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for bug 11251 -->
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/11251
//
// <-- Short Description -->
// execstr() could kill the stack

A = [];
assert_checkerror("execstr(""[A($+1),B] = 1;"")", [], 49);
assert_checkerror("[A($+1),B] = 1;", [], 49);
