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

b=list(1,2,3);
b(0)=0;
assert_checkequal(b, list(0,1,2,3));
assert_checkerror("b=list();b(-1)=1",_("Invalid index."));
assert_checkerror("b=list();b(-2)=2",_("Invalid index."));
