// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for issue 184 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/184
//
// <-- Short Description -->
// ImplicitList::compute for negative range, and positive step size

assert_checkequal(1:2:1, 1);
assert_checkequal(1:2:0, []);
assert_checkequal(1:-2:0, 1);
assert_checkequal(1:0:1, []);
