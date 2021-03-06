// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for issue 177 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/177
//
// <-- Short Description -->
// Handling of repeated indexes in Array<T>::remove

A=1:5;
A([2 2])=[];
assert_checkequal(A, [1 3 4 5]);
A([2 2 2])=[];
assert_checkequal(A, [1 4 5]);
