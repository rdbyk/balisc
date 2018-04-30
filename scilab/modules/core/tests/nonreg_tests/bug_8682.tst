// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Allan CORNET
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- ENGLISH IMPOSED -->

// <-- Non-regression test for bug 8682 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=8682
//
// <-- Short Description -->
// funcprot did not return the previous value when called with an argument.

deff('x = myplus(y, z)', 'x = y + z');
prot = funcprot(0); // one-line protection
deff('x=myplus(y,z)','x = y + z');
assert_checkequal(funcprot(prot), 0);
