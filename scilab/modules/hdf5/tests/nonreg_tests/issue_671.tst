// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
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

fname=TMPDIR+filesep()+"issue_671.sod";

v=list(null())
save(fname, "v")
clear v
load(fname, "v")
assert_checkequal(v, list(null()))

v=list(insert())
save(fname, "v")
clear v
load(fname, "v")
assert_checkequal(v, list(insert()))
