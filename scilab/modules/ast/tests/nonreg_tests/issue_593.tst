// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 593 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/593
//
// <-- Short Description -->
// Execution of "emptystr()+"ABCD"" yields a Crash

// scalar + scalar
assert_checkequal(emptystr()+"ABCD", "ABCD")

// matrix + scalar
assert_checkequal(emptystr(2,2)+"A", ["A","A";"A","A"])

// matrix + matrix
assert_checkequal(emptystr(2,2)+["A","B";"C","D"], ["A","B";"C","D"])
