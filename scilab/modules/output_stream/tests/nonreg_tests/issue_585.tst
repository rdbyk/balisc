// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 585 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/585
//
// <-- Short Description -->
// Execution of "msprintf("%0*d",4096,1)" yields Corrupted String

s=msprintf("%0*d", 4095, 1)
assert_checkequal(length(s), 4095)
assert_checkequal(part(s, 4095), "1")

s=msprintf("%0*d", 4096, 1)
assert_checkequal(length(s), 4096)
assert_checkequal(part(s, 4096), "1")

s=msprintf("%0*d", 6000, 1)
assert_checkequal(length(s), 6000)
assert_checkequal(part(s, 6000), "1")
