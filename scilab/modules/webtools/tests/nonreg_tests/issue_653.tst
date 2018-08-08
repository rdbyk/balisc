// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 653 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/653
//
// <-- Short Description -->
// Execution of "fromJSON("{""""}")" yields a Crash

err="fromJSON: JSON format expected."

assert_checkerror("fromJSON(""{""""""""}"")", err)
assert_checkerror("fromJSON(""{1}"")", err)
assert_checkerror("fromJSON(""{a}"")", err)
assert_checkerror("fromJSON(""{""""a""""}"")", err)

assert_checkequal(fromJSON("{a:123}"), struct("a",123))
assert_checkequal(fromJSON("{""a"":123}"), struct("a",123))
