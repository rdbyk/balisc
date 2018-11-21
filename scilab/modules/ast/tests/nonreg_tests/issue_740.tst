// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 740 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/740
//
// <-- Short Description -->
// Execution of "{1,2}'(1)" yields a Crash

assert_checkequal({1, 2}'(1), {1})
assert_checkequal({1, 2}'(2), {2})
