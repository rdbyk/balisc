// Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for issue 328 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/328
//
// <-- Short Description -->
// Protected Variables are Modified by "global" and "clearglobal"


global a b
protect();

errmsg = _("clearglobal: Redefining permanent variable.");

execstr("clearglobal a","errcatch");
assert_checkequal(lasterror(), errmsg);

execstr("clearglobal","errcatch");
assert_checkequal(lasterror(), errmsg);
