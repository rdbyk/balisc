// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 4943 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=4943
//
// <-- Short Description -->
// execstr does not check input arguments.

ierr = execstr("a=zzzzzzz","errcatch","n");

assert_checkerror("ierr = execstr(''a=zzzzzzz'',''errcatch'',''nooon'');", [], 110);
assert_checkerror("a=zzzzzzz", [], 40);
assert_checkerror("ierr = execstr(''a=zzzzzzz'',''errBADcatch'');", [], 110);
assert_checkerror("ierr = execstr(''a=zzzzzzz'',''errBADcatch'',''n'');", [], 110);
