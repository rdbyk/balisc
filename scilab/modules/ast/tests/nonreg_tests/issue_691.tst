// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 691 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/691
//
// <-- Short Description -->
// Subtraction of Scalar from "eye()" and vice versa yields Wrong Result

assert_checkequal(eye()-2, -1)
assert_checkequal(2-eye(), 1)

assert_checkequal(%i*eye()-1, -1+%i)
assert_checkequal(1-%i*eye(), 1-%i)

assert_checkequal(2*%i*eye()-%i, %i)
assert_checkequal(%i-2*%i*eye(), -%i)
