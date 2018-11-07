// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 731 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/731
//
// <-- Short Description -->
// Something after Continuation ".." within Matrix Expression Confuses Parser

ierr = execstr("[..TRASH", "errcatch")
assert_checktrue(ierr <> 0)
