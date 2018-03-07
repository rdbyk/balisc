// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 401 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/401
//
// <-- Short Description -->
// Results of "(0+0*%i)^(-1)" and "(0+0*%i)^%nan" are Wrong!

res=(0+0*%i)^(-1)
assert_checkequal(isinf(real(res)) && isnan(imag(res)), %t)

res=(0+0*%i)^%nan
assert_checkequal(isnan(real(res)) && isnan(imag(res)), %t)
