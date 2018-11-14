// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 744 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/744
//
// <-- Short Description -->
// Evaluation "p=1:$;p($)" yields Either a Crash or a Wrong Result

msg = _("Invalid index.")

p=1:2:$

assert_checkerror("p($+1)", msg)
assert_checkequal(p($), $)
assert_checkequal(p($-1), 2)
assert_checkequal(p($-2), 1)
assert_checkerror("p($-3)", msg)
