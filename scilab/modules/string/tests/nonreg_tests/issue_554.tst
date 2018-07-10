// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 554 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/554
//
// <-- Short Description -->
// Execution of "ascii(-1)" Does Not Raise Warning

warning("stop") // warning raises error

errmsg = ["*** Execution stopped after a warning. ***";"Set warning(""on"") to continue execution after a warning."]
assert_checkerror("ascii(-1)", errmsg)
assert_checkerror("ascii(256)", errmsg)
