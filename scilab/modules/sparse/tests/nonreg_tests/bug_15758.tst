// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2018 - Stéphane Mottelet
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 15758 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=15758
//
// <-- Short Description -->
// sparse([0 0],1) crashes scilab (regression)

msg = msprintf(_("%s: Wrong value(s) for input argument #%d: elements greater or equal to 1.0 expected.\n"), "sparse", 1);
assert_checkerror("sparse([0 0],1,[1 1])", msg);
assert_checkerror("sparse([0 1],1,[1 1])", msg);
assert_checkerror("sparse([1 0],1,[1 1])", msg);
msg = msprintf(_("%s: Wrong value(s) for input argument #%d: greater or equal to [2,1] expected.\n"), "sparse", 3);
assert_checkerror("sparse([2 1],1,[1 1])", msg);
msg = msprintf(_("%s: Wrong value(s) for input argument #%d: greater or equal to [1,2] expected.\n"), "sparse", 3);
assert_checkerror("sparse([1 2],1,[1 1])", msg);
msg = msprintf(_("%s: Wrong value(s) for input argument #%d: greater or equal to [2,2] expected.\n"), "sparse", 3);
assert_checkerror("sparse([2 2],1,[1 1])", msg);
