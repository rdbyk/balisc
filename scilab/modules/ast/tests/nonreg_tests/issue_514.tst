// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 514 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/514
//
// <-- Short Description -->
// Parsing of "[%t (2)]" or "["A" (2)]" is Wrong

assert_checkequal([%t 2], [1 2])
assert_checkequal([%f 2], [0 2])
assert_checkequal([%t (2)], [1 2])
assert_checkequal([%f (2)], [0 2])

assert_checkequal(["A" "B"], ["A" "B"])
assert_checkequal(["A" ("B")], ["A" "B"])
