// ============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Scilab Enterprises - Pierre-Aime AGNEL
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// ============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 14667 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=14667
//
// <-- Short Description -->
// Multi line string in a matrix without line feed generated a non terminal parser state

ierr = execstr(["A = [""some text ..."; ...
"ending here""]"], "errcatch");
assert_checktrue(ierr <> 0); // previous line must generate an error

ierr = execstr("A = ""some text ...", "errcatch");
assert_checktrue(ierr <> 0); // previous line must generate an error
