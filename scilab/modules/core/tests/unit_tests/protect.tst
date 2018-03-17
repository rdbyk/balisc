// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//

a=1
b=2

assert_checkequal(isprotected(["a","b"]),[%f,%f])

n = size(isprotected(),'*')

protect a b

ierr = execstr("a = 4","errcatch")
assert_checktrue(ierr <> 0)
ierr = execstr("b = 5","errcatch")
assert_checktrue(ierr <> 0)

assert_checkequal(size(isprotected(),'*'), n + 2)
assert_checkequal(isprotected(["a","b"]),[%t,%t])

unprotect b

ierr = execstr("b = 5","errcatch")
assert_checktrue(ierr == 0)
assert_checkequal(b, 5)

assert_checkequal(size(isprotected(),'*'), n + 1)
assert_checkequal(isprotected(["a","b"]),[%t,%f])

unprotect

ierr = execstr("a = 4","errcatch")
assert_checktrue(ierr == 0)
assert_checkequal(a, 4)

assert_checkequal(size(isprotected(),'*'), 0)
