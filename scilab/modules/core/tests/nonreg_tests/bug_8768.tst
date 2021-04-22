// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 8768 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=8768
//
// <-- Short Description -->
// GetRhsVar(..., STRING_DATATYPE did not check size of input argument

assert_checkerror("with_module([""ffa"", ""ff""])", [], 102);
assert_checkerror("clearfun([""myfuncA"", ""myfuncB""])", [], 102);
assert_checkerror("format([""e"", ""v""])", [], 999);
