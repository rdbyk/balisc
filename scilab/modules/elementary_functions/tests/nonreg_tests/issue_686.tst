// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 668 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/668
//
// <-- Short Description -->
// Execution of "base2dec(""G"",16)" does Not Raise an Error

msg = msprintf(_("%s: Wrong value for input argument #%d: Valid base %d representations expected.\n"), "base2dec", 1, 16);

assert_checkerror("base2dec(""G"",16)", msg)
assert_checkerror("base2dec(""g"",16)", msg)
