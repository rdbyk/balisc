// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 172 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/172
//
// <-- Short Description -->
// Crash caused by strsubst

errmsg = msprintf(_("%s: Delimiter must not be alphanumeric."),"strsubst")
assert_checkerror("strsubst(""pattern -- pattern __ pattern "",""pattern"",""replace"",""r"")", errmsg)
