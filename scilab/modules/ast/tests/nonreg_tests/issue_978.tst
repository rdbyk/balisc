// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 978 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/978
//
// <-- Short Description -->
// Execution of "for k=1:0,end" Corrupts Loop Variable

clear("k")
for k=1:0,end
assert_checkequal(isdef("k"),%f)

k=123
for k=1:0,end
assert_checkequal(k,123)
