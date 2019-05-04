// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Scilab Enterprises - Cedric Delamarre
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 14437 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=14437
//
// <-- Short Description -->
// Problem with the affectation cmde "=" applied to a "list of struct"

lst=list();
lst(1)=struct("f",[1,2]);
lst(2)=lst(1);
lst(2).f(2)=3;

assert_checkequal(lst(1).f, [1,2]);
assert_checkequal(lst(2).f, [1,3]);
