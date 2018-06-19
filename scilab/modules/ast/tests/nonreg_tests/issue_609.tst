// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 609 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/609
//
// <-- Short Description -->
// Execution of "A=1;A(%nan)" yields a Crash

assert_checkerror("A=1;A(%nan)", "Invalid index.")
