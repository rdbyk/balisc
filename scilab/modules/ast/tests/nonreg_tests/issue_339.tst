// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 339 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/339
//
// <-- Short Description -->
// Empty a Matrix using "X(:)=[]" is slooooooow!

X = ones(1000,1000);
tic()
X(:) = []
T = toc()

assert_checktrue(T < 0.01)
