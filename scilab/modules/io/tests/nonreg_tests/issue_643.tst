// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 643 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/643
//
// <-- Short Description -->
// Execution of "write(6,1:3,"(I2)")" yields a Crash

errmsg = "Incorrect file or format."
assert_checkerror("write(6,1:3,""(I2)"")", errmsg)
assert_checkerror("write(6,1:3,""(F10.3)"")", errmsg)
