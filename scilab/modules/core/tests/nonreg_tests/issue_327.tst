// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for issue 327 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/327
//
// <-- Short Description -->
// In Case of an Invalid Argument "global" Should only Raise an Error
// and Do Nothing Else

execstr("global a b 1c d e 2f","errcatch");
assert_checkequal(exists(["a","b","1c","d","2f"]), [0,0,0,0,0]);
