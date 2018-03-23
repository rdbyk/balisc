// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2018 - ESI Group - Adeline CARNIS
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 15422 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/15422
//
// <-- Short Description -->
// strsubst("ab", "", "cd") crashed Scilab

assert_checkequal(strsubst("ab", "", "cd"), "ab");
assert_checkequal(strsubst("", "", "cd"), "");
