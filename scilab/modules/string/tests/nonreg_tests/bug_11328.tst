// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - Scilab Enterprises - Vincent COUVERT
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 11328 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=11328
//
// <-- Short Description -->
// Wrong error message returned by strsplit when second input argument contained wrong values
//

S = "strsplit splits a string into a vector of strings";
assert_checkerror("strsplit(S, [15 25 130])", [], 110);
