// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 253 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/253
//
// <-- Short Description -->
// Set of Keywords returned by what() is wrong!

[p,k]=what();

assert_checkequal(intersect(p,k), []);
