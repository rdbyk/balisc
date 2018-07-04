// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 578 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/578
//
// <-- Short Description -->
// Multiplication of Polynomials is Buggy for Non-Finite Coefficients

p = %nan + %s
q = %inf + %s
assert_checkequal(isnan(coeff(p*p)), [%t %t %f])
assert_checkequal(isnan(coeff(p*q)), [%t %t %f])
assert_checkequal(isnan(coeff(q*p)), [%t %t %f])
assert_checkequal(isinf(coeff(q*q)), [%t %t %f])
