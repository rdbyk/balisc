// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Samuel GOUGEON
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 14513 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=14513
//
// <-- Short Description -->
//  isequal() comparing two builtin functions yielded an error

funcprot(0)

s = sin;
assert_checktrue(isequal(s, sin));

s = grand;
assert_checktrue(isequal(s, grand));

assert_checkfalse(isequal(cos, sin));
