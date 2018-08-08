// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 658 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/658
//
// <-- Short Description -->
// Execution of "{list()(:)}" yields a Crash

assert_checkerror("{list()(:)}", "Evaluation of element in cell expression failed.")
