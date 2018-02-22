// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 383 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/383
//
// <-- Short Description -->
// Result of "abs(complex(%inf,%nan))" is Wrong

assert_checkequal(abs(complex(%inf,%nan)), %nan)
assert_checkequal(abs(complex(%nan,%inf)), %nan)
assert_checkequal(abs(complex(%nan,%nan)), %nan)
