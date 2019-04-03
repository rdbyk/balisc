// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 810 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/810
//
// <-- Short Description -->
// Execution of "isvector(list())" yields a Crash

assert_checkequal(isvector(list()), %f)
