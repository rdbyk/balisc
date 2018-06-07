// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 580 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/580
//
// <-- Short Description -->
// Execution of "detr([])", "det(eye())" yields Wrong/Inconsistent Result

assert_checkequal(detr([]), 1)
assert_checkequal(detr(eye()),  1)
