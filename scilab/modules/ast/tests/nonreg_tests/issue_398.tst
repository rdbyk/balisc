// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 398 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/398
//
// <-- Short Description -->
// Sign of Result of "(-0)^(-n)" for Odd Integers n is Wrong!

assert_checkequal((-0)**(-1), -%inf)
assert_checkequal((-0)**(-2), %inf)
assert_checkequal((-0)**(-3), -%inf)
assert_checkequal((-0)**(-4), %inf)
assert_checkequal((-0)**(-5), -%inf)

assert_checkequal(1/(-0)**(1), -%inf)
assert_checkequal(1/(-0)**(2), %inf)
assert_checkequal(1/(-0)**(3), -%inf)
assert_checkequal(1/(-0)**(4), %inf)
assert_checkequal(1/(-0)**(5), -%inf)
