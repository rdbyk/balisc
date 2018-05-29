// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 553 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/553
//
// <-- Short Description -->
// Execution of "cell(-1)" yields a Crash

assert_checkequal(cell(-1), {})
assert_checkequal(cell(-1,-1), {})
assert_checkequal(cell(-1,-1,-1), {})
assert_checkequal(cell([-1 -1]), {})
assert_checkequal(cell([-1 -1 -1]), {})
