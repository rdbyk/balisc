// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 854 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/854
//
// <-- Short Description -->
// Execution of "copyfile("FOO","foo")" yields Unexpected Result, i.e. does Not Work

FOO=TMPDIR+'/FOO'
foo=TMPDIR+'/foo'

save(FOO)

assert_checkequal(copyfile(FOO,foo),1)
assert_checkequal(copyfile(FOO,FOO),0)
assert_checkequal(copyfile(foo,FOO),1)
