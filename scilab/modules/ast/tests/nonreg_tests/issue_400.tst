// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 400 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/400
//
// <-- Short Description -->
// Results of "(0+0*%i)^%i", "(0+0*%i)^(1+%i)", "(0+0*%i)^(-1+%i)", ... are Wrong!

res=(0+0*%i)^(0+%i)
assert_checkequal(isnan(real(res)) && isnan(imag(res)), %t)

assert_checkequal((0+0*%i)^(1+%i), complex(0,0))

res=(0+0*%i)^(-1+%i)
assert_checkequal(isinf(real(res)) && isnan(imag(res)), %t)

res=(0+0*%i)^(%nan+%i)
assert_checkequal(isnan(real(res)) && isnan(imag(res)), %t)
