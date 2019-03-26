// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 822 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/822
//
// <-- Short Description -->
// Execution of "s.a=1;getfield("b",s)" yields a Crash

s.a=1
assert_checkerror("getfield(''b'',s)",[],999)
