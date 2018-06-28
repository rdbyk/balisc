// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 619 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/619
//
// <-- Short Description -->
// Execution of "x=1;x()=[]" yields a Crash

errmsg = "Wrong insertion : Cannot insert without arguments."
assert_checkerror("x=1;x()=[]", errmsg)
assert_checkerror("x=[];x()=1", errmsg)
