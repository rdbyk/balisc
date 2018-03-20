// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 431 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/431
//
// <-- Short Description -->
// "s.b" and "s("b") Yield Different Results for a One-Element List in "b"

s=struct("a", list(1,2), "b", list(3))

assert_checkequal(s.b, list(3))
assert_checkequal(s("b"), list(3))
assert_checkequal(getfield("b",s), list(3))
