// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for issue 117 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/117
//
// <-- Short Description -->
// Calculation of powers of negative real numbers are wrong

assert_checkalmostequal((-1)^0.5, sqrt(-1), [], %eps);
assert_checkalmostequal((-2)^0.5, sqrt(-2), [], %eps);
assert_checkalmostequal((-2)^0.25, sqrt(sqrt(-2)), [], %eps);
