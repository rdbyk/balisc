// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 556 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/556
//
// <-- Short Description -->
// Execution "A(%nan)=1" does Not Raise an Error

assert_checkerror("A(%nan)=1", "Invalid index.")
assert_checkerror("B=1,B(%nan)=1", "Invalid index.")
