// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Charlotte HECQUET
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 11953 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=11953
//
// <-- Short Description -->
// Scilab crashes when global("") is entered.

assert_checkerror("global("""")", [], 110);
assert_checkerror("global(""a"","""")", [], 110);
assert_checkerror("global(""a"",""b"","""")",[], 110);

l=list("a", "b","c", "");
assert_checkerror("global(l(:))",[], 110);
