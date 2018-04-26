// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 411 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/411
//
// <-- Short Description -->
// "Integer Dot Division "./" by Zero yields a Crash"

assert_checkequal(int8(1)./0, int8(1)/0)
assert_checkequal(int8(-1)./0, int8(-1)/0)
assert_checkequal(int8(0)./0, int8(0)/0)

assert_checkequal(uint8(1)./0, uint8(1)/0)
assert_checkequal(uint8(-1)./0, uint8(-1)/0)
assert_checkequal(uint8(0)./0, uint8(0)/0)

assert_checkequal(int16(1)./0, int16(1)/0)
assert_checkequal(int16(-1)./0, int16(-1)/0)
assert_checkequal(int16(0)./0, int16(0)/0)

assert_checkequal(uint16(1)./0, uint16(1)/0)
assert_checkequal(uint16(-1)./0, uint16(-1)/0)
assert_checkequal(uint16(0)./0, uint16(0)/0)

assert_checkequal(int32(1)./0, int32(1)/0)
assert_checkequal(int32(-1)./0, int32(-1)/0)
assert_checkequal(int32(0)./0, int32(0)/0)

assert_checkequal(uint32(1)./0, uint32(1)/0)
assert_checkequal(uint32(-1)./0, uint32(-1)/0)
assert_checkequal(uint32(0)./0, uint32(0)/0)

assert_checkequal(int64(1)./0, int64(1)/0)
assert_checkequal(int64(-1)./0, int64(-1)/0)
assert_checkequal(int64(0)./0, int64(0)/0)

assert_checkequal(uint64(1)./0, uint64(1)/0)
assert_checkequal(uint64(-1)./0, uint64(-1)/0)
assert_checkequal(uint64(0)./0, uint64(0)/0)
