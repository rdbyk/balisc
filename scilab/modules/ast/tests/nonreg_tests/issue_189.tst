// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for issue 189 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/189
//
// <-- Short Description -->
// Missing Imaginary Parts of Automatically Inserted Zeros in Complex Polynomials

P=[%s+%i];
P(3)=3;
assert_checkequal(isreal(P(1)), %f);
assert_checkequal(isreal(P(2)), %f);
assert_checkequal(isreal(P(3)), %f);
assert_checkequal(P, [%s+%i; 0; 3]);
