// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Allan CORNET
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- JAVA NOT MANDATORY -->
//
// <-- Non-regression test for bug 11110 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=11110
//
// <-- Short Description -->
// poly() result was wrong on windows x64
//

REF = poly([0 2 2 1],'s','coeff')

r = poly([0 -1+%i -1-%i],'s',"roots");
assert_checkequal(r, REF);

r = poly([-1+%i 0 -1-%i],'s',"roots");
assert_checkequal(r, REF);

r = poly([-1+%i -1-%i 0],'s',"roots");
assert_checkequal(r, REF);

r = poly([-1-%i -1+%i 0],'s',"roots");
assert_checkequal(r, REF);
