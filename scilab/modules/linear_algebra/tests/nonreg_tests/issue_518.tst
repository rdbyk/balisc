// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 518 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/518
//
// <-- Short Description -->
// Execution of "norm(eye())" triggers Warning Message of LAPACK library

assert_checkequal(norm(eye()), 1)
assert_checkequal(norm(eye(),1), 1)
assert_checkequal(norm(eye(),2), 1)
assert_checkequal(norm(eye(),3), 1)
assert_checkequal(norm(eye(),%inf), 1)
assert_checkequal(norm(eye(),"inf"), 1)
assert_checkequal(norm(eye(),"fro"), 1)

a = 1 + %i;
b = abs(a);

assert_checkequal(norm(a*eye()), b)
assert_checkequal(norm(a*eye(),1), b)
assert_checkequal(norm(a*eye(),2), b)
assert_checkequal(norm(a*eye(),3), b)
assert_checkequal(norm(a*eye(),%inf), b)
assert_checkequal(norm(a*eye(),"inf"), b)
assert_checkequal(norm(a*eye(),"fro"), b)
