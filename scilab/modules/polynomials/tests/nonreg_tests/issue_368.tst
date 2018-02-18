// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 368 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/368
//
// <-- Short Description -->
// Inconsistent Acceptance of Variable Names by Function "poly"


poly([1 2 3],"x")
poly([1 2 3],"x1")
poly([1 2 3],"!x")
