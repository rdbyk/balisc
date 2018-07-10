// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 482 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/482
//
// <-- Short Description -->
// Execution of "S=struct();S(2,2)=struct()" yields a Crash

errmsg = "Submatrix incorrectly defined."

assert_checkerror("S=struct();S(2,2)=struct()", errmsg)
assert_checkerror("T(2,2)=struct()", errmsg)
