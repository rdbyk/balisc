// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 399 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/399
//
// <-- Short Description -->
// Results of "0^(%i)" and "0^(%nan+%i) are Wrong!

res=0^%i
assert_checkequal(isnan(real(res)) && isnan(imag(res)), %t)

assert_checkequal(0^(1+%i), complex(0,0))

res=0^(-1+%i)
assert_checkequal(isinf(real(res)) && isnan(imag(res)), %t)

res=0^(%nan+%i)
assert_checkequal(isnan(real(res)) && isnan(imag(res)), %t)
