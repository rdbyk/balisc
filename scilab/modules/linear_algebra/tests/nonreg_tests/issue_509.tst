// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 509 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/509
//
// <-- Short Description -->
// Wrong Result of "inv" for Complex Multiples of "eye"

assert_checkequal(inv(2*eye()), 1/2*eye())
assert_checkequal(inv((1+%i)*eye()), 1/(1+%i)*eye())
