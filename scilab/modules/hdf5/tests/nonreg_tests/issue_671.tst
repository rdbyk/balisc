// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 671 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/671
//
// <-- Short Description -->
// List containing "null()" or "insert()" can't be saved

v=list(null())
save(TMPDIR+pathsep()+"issue_671.sod", "v")
clear v
load(TMPDIR+pathsep()+"issue_671.sod", "v")
assert_checkequal(v, list(null()))

v=list(insert())
save(TMPDIR+pathsep()+"issue_671.sod", "v")
clear v
load(TMPDIR+pathsep()+"issue_671.sod", "v")
assert_checkequal(v, list(insert()))
