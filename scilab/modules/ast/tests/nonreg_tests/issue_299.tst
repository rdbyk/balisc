// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 299 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/299
//
// <-- Short Description -->
// (Un)defined Operations for Boolean Values

assert_checkequal(%f+%f, 0)
assert_checkequal(%f+%t, 1)
assert_checkequal(%t+%f, 1)
assert_checkequal(%t+%t, 2)

assert_checkequal(%f-%f, 0)
assert_checkequal(%f-%t, -1)
assert_checkequal(%t-%f, 1)
assert_checkequal(%t-%t, 0)

assert_checkequal(%f*%f, 0)
assert_checkequal(%f*%t, 0)
assert_checkequal(%t*%f, 0)
assert_checkequal(%t*%t, 1)

assert_checkequal(%f/%f, %nan)
assert_checkequal(%f/%t, 0)
assert_checkequal(%t/%f, %inf)
assert_checkequal(%t/%t, 1)

assert_checkequal(%f.*%f, 0)
assert_checkequal(%f.*%t, 0)
assert_checkequal(%t.*%f, 0)
assert_checkequal(%t.*%t, 1)

assert_checkequal(%f./%f, %nan)
assert_checkequal(%f./%t, 0)
assert_checkequal(%t./%f, %inf)
assert_checkequal(%t./%t, 1)

assert_checkequal(-%f, 0)
assert_checkequal(-%t, -1)
