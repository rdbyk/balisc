//<-- CLI SHELL MODE -->
// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

//<-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 3687 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=3687
//
// <-- Short Description -->
// "format" doesn't check input value 

current_format = format();

a = format();
if and(a <> [1 10]) then pause,end

format(2);
b = format();
if and(b <> [1 2]) then pause,end

assert_checkerror('format(300000000000000000000000000)', [], 111);
assert_checkerror('format(-1)', [], 999);
assert_checkerror('format(1)', [], 999);


format('v',12)
b = format();
if and(b <> [1 12]) then pause,end

format(13,'v')
b = format();
if and(b <> [1 13]) then pause,end
