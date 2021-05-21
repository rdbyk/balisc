// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Charlotte HECQUET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 9851 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/9851
//
// <-- Short Description -->
// Error message occurs because of a cut-off frequency of 0.25Hz with irr

hz=iir(2,'lp','butt',[0.25 0.25],[0 0]);
z=poly(0,'z');
num=0.29289321881345 +0.58578643762690*z +0.292893218813452427*z^2
den=0.17157287525381 +3.52180785161D-17*z +z^2;
assert_checkalmostequal(coeff(hz.num), coeff(num));
assert_checkalmostequal(coeff(hz.den), coeff(den));
