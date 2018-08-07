// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 570 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/570
//
// <-- Short Description -->
// Execution of "speye(-1,-1)" yields a Crash

assert_checkequal(speye(-1,-1), sparse([],[]))

errmsg="sparse: Wrong value(s) for input argument #1: elements greater or equal to 1.0 expected."
assert_checkerror("sparse([0,0],1)", errmsg)

errmsg="sparse: Wrong value(s) for input argument #3: greater or equal to [5,5] expected."
assert_checkerror("sparse([5,5],6,[1,1])", errmsg)
