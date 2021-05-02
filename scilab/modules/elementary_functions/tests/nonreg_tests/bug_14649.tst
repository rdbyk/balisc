// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Samuel GOUGEON
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 14649 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=14649
//
// <-- Short Description -->
//  isnan(complex(%inf, %inf)) returned %F

C = complex([-%inf -%inf %inf %inf], [-%inf %inf -%inf %inf]);
res = [%f %f %f %f];
assert_checkequal(isnan(C), res);
assert_checkequal(isnan(sparse(C)), sparse(res));
