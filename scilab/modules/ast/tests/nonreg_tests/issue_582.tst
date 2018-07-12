// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 582 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/582
//
// <-- Short Description -->
// Execution of "if who(),end" et. al. yields a Crash

a=0

if who()
    a = 1
else
    a = 2
end

assert_checkequal(a, 2)

a = 0

while who()
    a = 3
end

assert_checkequal(a, 0)

assert_checkerror("for w=who(),end", "for expression : No value for assignment to loop variable.")
