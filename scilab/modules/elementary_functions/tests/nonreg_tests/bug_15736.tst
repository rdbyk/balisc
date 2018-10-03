// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2018 - Samuel GOUGEON
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 15736 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/15736
//
// <-- Short Description -->
// unique failed with complex numbers.

assert_checkequal(unique([1 %i]),[%i 1]);
