// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Charlotte Hecquet
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// Singular values
assert_checkequal(sinc(0),1);
assert_checkequal(sinc(-0),1);
assert_checktrue(isnan(sinc(%inf))==%t);
assert_checktrue(isnan(sinc(%nan))==%t);
// Vector
x=linspace(1,%pi,100);
assert_checkalmostequal(sinc(x),sin(x)./x, [], 1e-12);
assert_checkalmostequal(sinc(-x),sinc(x), [], 1e-12);
// Hypermat
x2=rand(2,2,2,2);
assert_checkalmostequal(sinc(x2),sin(x2)./x2, [], 1e-12);
// Sparse
x2=sparse(x);
assert_checkalmostequal(sinc(x2),full(sin(x2)./x2), [], 1e-12);

// Error messages
assert_checkerror("sinc(1,2,3)", [], 71);
assert_checkerror("sinc()", [], 71);
assert_checkerror("sinc(""test"")", [], 90);
assert_checkerror("sinc(list(1,2,3))", [], 90);
assert_checkerror("sinc(abs)", [], 90);
assert_checkerror("sinc(poly(0,''s''))", [], 90);
A=[0,1;0,0];B=[1;1];C=[1,1];
S1=syslin("c",A,B,C);
assert_checkerror("sinc(S1)", [], 90);
assert_checkerror("sinc(ss2tf(S1))", [], 90);
