// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 748 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/748
//
// <-- Short Description -->
// Extraction from Implicit List is Buggy

p=1:2:$

assert_checkequal(p([1 2]), [1 2])
assert_checkequal(p([2 3]), [2 $])
assert_checkequal(p([3 1 2]), [$ 1 2])
assert_checkequal(p([2 3 1]'), [2;$;1])
assert_checkequal(p([3 3 3 3]), [$ $ $ $])
assert_checkequal(p(:), [1;2;$])
