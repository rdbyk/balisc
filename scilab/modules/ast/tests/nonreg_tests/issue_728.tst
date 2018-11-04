// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 728 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/728
//
// <-- Short Description -->
// Execution of "a(list())=1" or "a{list()}=1" yields a Crash

msg = _("Wrong insertion : Cannot insert without arguments.")

assert_checkerror("a(list())=1", msg)

clear a
assert_checkerror("a{list()}=1", msg)
