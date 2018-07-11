// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 312 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/312
//
// <-- Short Description -->
// Commands "a=2; a{1}=3" yield Corrupted Result Without any Sign of Failure

errmsg = "Cell indexing ""{..}"" of non-cell objects is not allowed."

assert_checkerror("b=%t;b{2}=1", errmsg)
assert_checkerror("a=2;a{2}=1", errmsg)
assert_checkerror("s="""";s{2}=1", errmsg)
assert_checkerror("p=%s;p{2}=1", errmsg)
assert_checkerror("S=struct();S{2}=1", errmsg)
assert_checkerror("L=list();L{2}=1", errmsg)
