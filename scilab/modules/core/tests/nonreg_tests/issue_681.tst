// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 681 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/681
//
// <-- Short Description -->
// Argument Checking in "null" and "insert" Function is Really Poor! 

errmsg=msprintf(_("%s: Wrong number of input arguments: %d expected."), "null", 0);
assert_checkerror("null(1)",errmsg)

errmsg=msprintf(_("%s: Wrong number of input arguments: %d to %d expected."), "insert", 0, 1);
assert_checkerror("insert(1,2)",errmsg)
