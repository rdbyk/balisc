// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 601 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/601
//
// <-- Short Description -->
// Predecence of Colon ":" Operator

assert_checkequal(1:2==3:4, [%f,%f])
assert_checkequal(1:2==(3:4), [%f,%f])
assert_checkequal((1:2)==(3:4), [%f,%f])
