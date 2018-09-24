// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 443 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/443
//
// <-- Short Description -->
// Trying to Assign List Operations Does Not Work

a = null()
assert_checkequal(typeof(a), "listdelete")

a = insert()
assert_checkequal(typeof(a), "listinsert")

// FIXME: cumbersome creation of "Undefined"
a = list()
a(1) = insert()
a = a(1)
assert_checkequal(typeof(a), "listundefined")
