// Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 480 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/480
//
// <-- Short Description -->
// Execution of "1:null()" or "1:insert()" yields a Crash

assert_checkerror("1:null()", [], 41)
assert_checkerror("1:insert()", [], 41)

assert_checkequal((1:1):2, [1,2])
assert_checkequal((1:1):(2:2), [1,2])
assert_checkerror("1:(2:3)", [], 41)
