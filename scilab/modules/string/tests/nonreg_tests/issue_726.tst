// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 726 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/726
//
// <-- Short Description -->
// Execution of "strsubst("aaa","aa","a")" yields a Crash

assert_checkequal(strsubst("AAA","AA","A"), "AA")
assert_checkequal(strsubst("BAAABAABABAA","AA","A"), "BAABABABA")
