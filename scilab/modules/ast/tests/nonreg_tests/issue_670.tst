// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 670 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/670
//
// <-- Short Description -->
// Execution of "a.b=a.b" may yield a Crash

a=struct("b",1)
a.b=a.b
