// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2006-2008 - INRIA - Allan CORNET <allan.cornet@inria.fr>
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 2332 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=2332
//

assert_checkerror("mprintf(""a: %2.0f\tb: %3.4f"",10)", [], 150);
assert_checkerror("mprintf(""a: %2.0f"")", [], 150);
