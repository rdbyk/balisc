// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 385 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/385
//
// <-- Short Description -->
// Result of "abs(complex(%inf,%inf))" is Wrong

assert_checkequal(abs(complex(%inf,%inf)), %inf)
assert_checkequal(abs(complex(%inf,-%inf)), %inf)
assert_checkequal(abs(complex(-%inf,%inf)), %inf)
assert_checkequal(abs(complex(-%inf,-%inf)), %inf)
