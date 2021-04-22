// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2010 - DIGITEO - Allan CORNET
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- Non-regression test for bug 7946 -->
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// 
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=7946
//
// <-- Short Description -->
// error(0, "bye") crashed Scilab

assert_checkerror("error(-10, ""bye"");", [], 110);
assert_checkerror("error(2000, ""Hello"");", "Hello", 2000);
