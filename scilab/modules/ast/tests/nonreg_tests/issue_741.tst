// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 741 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/741
//
// <-- Short Description -->
// Evaluation of "p=1:$;p(4)" Does Not Raise an Error

msg = _("Invalid index.")

p=1:$

assert_checkerror("p(0)", msg)
assert_checkerror("p(4)", msg)
