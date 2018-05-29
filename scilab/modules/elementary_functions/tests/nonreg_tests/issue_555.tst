// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 555 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/555
//
// <-- Short Description -->
// Execution of "eye(-1,-1)" yields Not An Empty Matrix "[]"

assert_checkequal(eye(1,0), [])
assert_checkequal(eye(0,1), [])
assert_checkequal(eye(0,0), [])
assert_checkequal(eye(0,-1), [])
assert_checkequal(eye(-1,0), [])
assert_checkequal(eye(-1,-1), [])
assert_checkequal(eye(-2,-2), [])
assert_checkequal(eye(1,0,1), [])
assert_checkequal(eye(1,-1,1), [])
assert_checkequal(eye(-1,-1,-1), [])
