// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for issue 148 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/148
//
// <-- Short Description -->
// Fix Handling of Negative Indices in List::insert

a=list(1,2,3);
b=a;

// ListDelete
a(0) = null();
assert_checkequal(a, b);
a(-1) = null();
assert_checkequal(a, b);
a(1) = null();
assert_checkequal(a, list(2,3));

a(0)=1;
assert_checkequal(a, b);
a(-1)=1;
assert_checkequal(a, b);
a(1)=5;
assert_checkequal(a, list(5,2,3));
