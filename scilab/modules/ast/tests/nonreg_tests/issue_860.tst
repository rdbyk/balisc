// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 860 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/860
//
// <-- Short Description -->
// Execution of "[]()" yields a Syntax Error

assert_checkequal([](),[])
assert_checkequal({}(),{})
assert_checkequal(1(),1)
assert_checkequal(sin(1)(),sin(1))
