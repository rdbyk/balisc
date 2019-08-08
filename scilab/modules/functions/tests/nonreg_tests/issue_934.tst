// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 934 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/934
//
// <-- Short Description -->
// Keyword Arguments in "varargin" are Nonsense ...

function f(varargin),end
assert_checkerror("f(a=1)",[],60)
