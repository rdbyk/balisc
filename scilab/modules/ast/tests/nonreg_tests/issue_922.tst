// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 922 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/922
//
// <-- Short Description -->
// Execution of "1 | who()" yields a Crash

assert_checkerror("~who()",[],42)
assert_checkerror("1 | who()",[],42)
assert_checkerror("1 & who()",[],42)
assert_checkerror("0 || who()",[],42) // shortcut op !!!
assert_checkerror("1 && who()",[],42)
assert_checkerror("who() | 1",[],42)
assert_checkerror("who() & 1",[],42)
assert_checkerror("who() || 1",[],42)
assert_checkerror("who() && 1",[],42)
