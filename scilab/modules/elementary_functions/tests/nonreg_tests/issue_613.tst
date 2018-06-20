// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 613 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/613
//
// <-- Short Description -->
// Execution of "int(1e19)" yields Blatantly Wrong Result

assert_checkequal(int(1e10), 1e10)
assert_checkequal(int(1e20), 1e20)
assert_checkequal(int(1e200), 1e200)
assert_checkequal(int(1e400), %inf)
