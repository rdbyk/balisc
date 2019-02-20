// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Antoine ELIAS
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- ENGLISH IMPOSED -->
//
// <-- Non-regression test for bug 15106 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/15106
//
// <-- Short Description -->
// Operation with null operand crashs Scilab

assert_checkerror("whereami() == ""SCI""", [], 42);
assert_checkerror("""SCI"" == whereami()", [], 42);
