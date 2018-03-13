// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 412 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/412
//
// <-- Short Description -->
// Execution of "%t./%f" yields a Crash

assert_checkequal(%f./%f, %nan)
assert_checkequal(%f./%t, 0)
assert_checkequal(%t./%f, %inf)
assert_checkequal(%t./%t, 1)
