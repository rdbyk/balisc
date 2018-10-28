// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 719 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/719
//
// <-- Short Description -->
// Parsing of Matrix Expressions is Sloppy

msg = _("Error: syntax error, unexpected "",""")

assert_checkerror("[1,,2]",["[1,,2]";"    ^";msg])
assert_checkerror("[,1,2]",["[,1,2]";"  ^";msg])
assert_checkerror("[1;,2]",["[1;,2]";"    ^";msg])

msg = _("Error: syntax error, unexpected ;")

assert_checkerror("[1;;2]",["[1;;2]";"    ^";msg])
assert_checkerror("[;1;2]",["[;1;2]";"  ^";msg])
assert_checkerror("[1,;2]",["[1,;2]";"    ^";msg])
