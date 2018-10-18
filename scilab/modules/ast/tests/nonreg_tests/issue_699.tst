// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 699 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/699
//
// <-- Short Description -->
// Execution of "a{1}=null()" yields a Crash

a{1}=null()
b{1}=insert()
c{1}=void()
