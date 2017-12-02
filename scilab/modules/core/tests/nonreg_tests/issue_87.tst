// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for issue 87 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/87
//
// <-- Short Description -->
// Computation of implicit lists is inconsistent/wrong for floating
// point arguments 

// a < b < c
a=nearfloat("pred",5);
b=5;
c=nearfloat("succ",5);

assert_checkequal(1:a, [1,2,3,4]);
assert_checkequal(1:b, [1,2,3,4,5]);
assert_checkequal(1:c, [1,2,3,4,5]);
assert_checkequal(a:-1:1, a-[0,1,2,3]);
assert_checkequal(b:-1:1, b-[0,1,2,3,4]);
assert_checkequal(c:-1:1, c-[0,1,2,3,4]);

// step and end values _not_ exactly representable by double floats
assert_checkalmostequal(0:0.1:0.1, [0.0,0.1]);
assert_checkalmostequal(0:0.1:0.2, [0.0,0.1,0.2]);
assert_checkalmostequal(0:0.1:0.3, [0.0,0.1,0.2,0.3]);
assert_checkalmostequal(0:0.1:0.4, [0.0,0.1,0.2,0.3,0.4]);
assert_checkalmostequal(0:0.1:0.5, [0.0,0.1,0.2,0.3,0.4,0.5]);
assert_checkalmostequal(0:0.1:0.6, [0.0,0.1,0.2,0.3,0.4,0.5,0.6]);
