// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Calixte DENIZET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 10428 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/10428
//
// <-- Short Description -->
//
// Java apps shew a library load error in CLI

assert_checkerror("xcos", [], 26);
assert_checkerror("scinotes", [], 26);
assert_checkerror("browsehistory", [], 26);
assert_checkerror("browsevar", [], 26);
assert_checkerror("filebrowser", [], 26);
assert_checkerror("editvar(''a'')", [], 26);
assert_checkerror("driver(''png'')", [], 26);
assert_checkerror("plot2d()", [], 26);
