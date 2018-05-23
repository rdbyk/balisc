// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 544 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/544
//
// <-- Short Description -->
// Execution of "det([])" yields "0" and "det(eye[])" yields Error

assert_checkequal(det([]), 1)
assert_checkequal(det(eye()), 1)
assert_checkequal(det(2*eye()), 2)
assert_checkequal(det((1+%i)*eye()), 1+%i)
