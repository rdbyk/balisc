// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 416 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/416
//
// <-- Short Description -->
// Function "string" does Not Convert Integers Properly

assert_checkequal(string(uint32(123456789), "123456789")
