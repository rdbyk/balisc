// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 546 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/546
//
// <-- Short Description -->
// Execution of "eye()*eye()" yields Wrong Result and LAPACK Error

A=2*eye();
B=(3+4*%i)*eye();

assert_checkequal(A*A, 4*eye())
assert_checkequal(A*B, (6+8*%i)*eye())
assert_checkequal(B*A, (6+8*%i)*eye())
assert_checkequal(B*B, (-7+24*%i)*eye())
