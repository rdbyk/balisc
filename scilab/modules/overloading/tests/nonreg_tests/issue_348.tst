// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for issue 348 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/348
//
// <-- Short Description -->
// Upper Triangular "triu" yields Wrong Result for String Matrices

assert_checkequal(triu(["a","b";"c","d"]), ["a","b";"","d"]);
