// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2018 - Stéphane Mottelet
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 15648 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=15648
//
// <-- Short Description -->
// sparse([1 1],1,[-1 -1])  crashes scilab

errMsg = _("%s: Wrong value(s) for input argument #%d: greater or equal to [1,1] expected.\n")
assert_checkerror("sparse([1 1],1,[-1 -1])",msprintf(errMsg, "sparse", 3));
