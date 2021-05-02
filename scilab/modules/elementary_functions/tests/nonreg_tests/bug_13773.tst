// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Anais AUBERT
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 13773 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=13773
//
// <-- Short Description -->
// save with negative second argument dit not trigger an error

assert_checkerror("size(ones(2,3),0)", [], 110);
assert_checkerror("size(ones(2,3),-1)", [], 110);
assert_checkerror("size(ones(2,3),-2)", [], 110);
