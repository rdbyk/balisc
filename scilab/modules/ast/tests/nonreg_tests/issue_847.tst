// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 847 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/847
//
// <-- Short Description -->
// Removal of Last Field Does Not Resize Struct Array to Empty

s.a=1
s.b=2

rmfield("a",s)
assert_checkequal(size(s,'*'),1)

rmfield("b",s)
assert_checkequal(size(s,'*'),0)
