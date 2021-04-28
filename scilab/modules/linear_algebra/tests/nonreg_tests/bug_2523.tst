// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2005-2008 - INRIA Serge Steer
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 2523 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=2523
//
// <-- Short Description -->
// slash and backslash matrix divisions involving vectors with %inf or %nan entries
// hang scilab


assert_checkerror("[1 %inf]\1", [], 39);
assert_checkerror("[1 2]\%inf", [], 39);

assert_checkerror("[1+%i %inf]\1", [], 39);
assert_checkerror("[1+%i %inf]\%i", [], 39);

assert_checkerror("[1 %i]\%inf", [], 39);

assert_checkerror("1/[1 %inf]", [], 39);
assert_checkerror("%inf/[1 2]", [], 39);

assert_checkerror("1/[1+%i %inf]", [], 39);
assert_checkerror("%i/[1+%i %inf]", [], 39);

assert_checkerror("%inf/[1 %i]", [], 39);
