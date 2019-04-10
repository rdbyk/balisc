// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 840 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/840
//
// <-- Short Description -->
// Not-Equal Relation "<>" may yield Wrong Result for Polynomials

p=poly([1 %nan], "s", "coeff")
assert_checktrue(p<>p)

assert_checkfalse(1+%s<>1+%s)
assert_checktrue(1+%s<>1+2*%s)
assert_checktrue(2+%s<>1+%s)
assert_checktrue(1+%s<>2+2*%s)
