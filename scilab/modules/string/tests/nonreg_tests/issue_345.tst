// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for issue 345 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/345
//
// <-- Short Description -->
// Using Empty String as 2nd Arg in "strsubst" may yield a Crash

assert_checkequal(strsubst("A","","B"), "A");
assert_checkequal(strsubst("A","",""), "A");
assert_checkequal(strsubst("","",""), "");
