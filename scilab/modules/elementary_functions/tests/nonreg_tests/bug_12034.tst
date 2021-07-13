// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Charlotte HECQUET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 12034 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=12034
//
// <-- Short Description -->
// The max function does not manage empty matrix.

assert_checkequal(max([],[],[]), []);

assert_checkerror("max([],1,1)", [], 110);
assert_checkerror("max(1,[],[])", [], 110);
assert_checkerror("max(1,1,[])", [], 110);
