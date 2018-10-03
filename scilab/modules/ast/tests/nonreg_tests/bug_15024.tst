// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2018 - Stéphane MOTTELET
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for bug 15024 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/15024
//
// <-- Short Description -->
// After A=10;  A{1}=2  corrupts A and silently fails

msg = sprintf(_("Cell indexing ""{..}"" of non-cell objects is not allowed.\n")); 
assert_checkerror("A=10;A{1}=2", msg);
