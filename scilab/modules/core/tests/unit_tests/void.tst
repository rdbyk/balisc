// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//

assert_checktrue(typeof(void())=="listundefined")

errmsg=msprintf(_("%s: Wrong number of input arguments: %d expected."), "void", 0);
assert_checkerror("void(1)",errmsg)
