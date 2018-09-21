// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 667 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/667
//
// <-- Short Description -->
// Using "insert()" may Fatally Corrupt a List with a Crash as Consequence

L=list()
L(2)=insert()
L(1)
