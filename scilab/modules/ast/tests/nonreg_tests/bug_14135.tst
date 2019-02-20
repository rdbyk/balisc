// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Cedric Delamarre
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 14135 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/14135
//
// <-- Short Description -->
// crash when running "Graphics -> Matplot -> Java Image" demonstration.
// argument of a "function call"/"extraction" must be treated before the function/variable.

assert_checkerror("a(b)", [], 40);
