// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 672 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/672
//
// <-- Short Description -->
// Execution of "sin{1}=1" yields a Crash

msg = _("Cell indexing ""{..}"" of non-cell objects is not allowed.")

assert_checkerror("sin{1}=1",msg)
assert_checkerror("sinm{1}=1",msg)
