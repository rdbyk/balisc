// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Paul Bignier
// Copyright (C) ????-2008 - INRIA
// Copyright (C) 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

res = buildouttb([2 2], 1); // Request a list containing a 2x2 matrix of doubles

resRef = list([0 0; 0 0]);
assert_checkequal(res, resRef);


refMsg = msprintf(_("%s: Wrong number of input arguments: %d expected."), "buildouttb", 2);
assert_checkerror("buildouttb()", refMsg);
