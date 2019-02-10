// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 775 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/775
//
// <-- Short Description -->
// Kronecker Div Ops "1./.0" and "0.\.1" Always Raise an Error

ieee(2);

assert_checkequal(1./.0, %inf)
assert_checkequal(0.\.1, %inf)

ieee(1);
warning("on");
assert_checkequal(1./.0, %inf)
assert_checkequal(0.\.1, %inf)

warning("off");
assert_checkequal(1./.0, %inf)
assert_checkequal(0.\.1, %inf)

warning("stop");
assert_checkerror("1./.0", [], 999)
assert_checkerror("0.\.1", [], 999)

ieee(0);
assert_checkerror("1./.0", [], 36)
assert_checkerror("0.\.1", [], 36)
