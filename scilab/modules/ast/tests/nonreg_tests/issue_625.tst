// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- TEST WITH GRAPHIC -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 625 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/625
//
// <-- Short Description -->
// Element Removal "H[k]=[]" does Not Work for Handle Arrays

h=gcf()

H=[h,h,h]
assert_checkequal(length(H), 3)

H(2)=[]
assert_checkequal(length(H), 2)

H($+1)=h
assert_checkequal(length(H), 3)
