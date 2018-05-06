// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 507 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/507
//
// <-- Short Description -->
// Wrong Results of Div Ops with Multiples of "eye"

assert_checkequal(1/(2*eye()), 1/2)
assert_checkequal((2*eye())/1, 2*eye())
assert_checkequal((2*eye())/(3*eye()), (2/3)*eye())

assert_checkequal(1\(2*eye()), 2*eye())
assert_checkequal((2*eye())\1, 1/2)
assert_checkequal((2*eye())\(3*eye()), (3/2)*eye())
