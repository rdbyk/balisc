// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 713 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/713
//
// <-- Short Description -->
// Execution of "imult(%s)" yields a Crash

assert_checkequal(imult(%s), %s*%i)
assert_checkequal(imult(%s*%i), -%s)
