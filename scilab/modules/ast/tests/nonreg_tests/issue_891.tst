// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 891 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/891
//
// <-- Short Description -->
// Execution of "1:1e10" yields "[]"


assert_checkerror("1:1e10",[],34)
