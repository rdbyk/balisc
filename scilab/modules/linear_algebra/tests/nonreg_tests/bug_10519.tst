// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Vincent COUVERT
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

// <-- Non-regression test for bug 10519 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=10519
//
// <-- Short Description -->
// Wrong error message in spec function when input arguments were not square.

// First input argument is not square
assert_checkerror("spec(rand(1,2),rand(2,4))", [], 103);

// Second input argument is not square
assert_checkerror("spec(rand(2,2),rand(2,4))", [], 103);
