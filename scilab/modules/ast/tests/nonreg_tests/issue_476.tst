// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 476 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/476
//
// <-- Short Description -->
// Execution of "[null(),null()]" or "[insert(),insert()]" yields a Crash

assert_checkerror("[null(),null()]", [], 999)
assert_checkerror("[null();null()]", [], 999)

assert_checkerror("[1,null()]", [], 999)
assert_checkerror("[null(),1]", [], 999)

assert_checkerror("[1;null()]", [], 999)
assert_checkerror("[null();1]", [], 999)
