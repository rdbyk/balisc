// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Unit test "intmin" -->

assert_checkequal(intmin(),int32(-2147483648)) // default 'int32'

assert_checkequal(intmin('int8'),int8(-128))
assert_checkequal(intmin('int16'),int16(-32768))
assert_checkequal(intmin('int32'),int32(-2147483648))
assert_checkequal(intmin('int64'),-int64(2)^63)

assert_checkequal(intmin('uint8'),uint8(0))
assert_checkequal(intmin('uint16'),uint16(0))
assert_checkequal(intmin('uint32'),uint32(0))
assert_checkequal(intmin('uint64'),uint64(0))

si8=int8(-1)
si16=int16(3)
si32=int32(-5)
si64=int64(7)
ui8=uint8(2)
ui16=uint16(4)
ui32=uint32(6)
ui64=uint64(8)

assert_checkequal(intmin(si8),int8(-128))
assert_checkequal(intmin(si16),int16(-32768))
assert_checkequal(intmin(si32),int32(-2147483648))
assert_checkequal(intmin(si64),-int64(2)^63)

assert_checkequal(intmin(ui8),uint8(0))
assert_checkequal(intmin(ui16),uint16(0))
assert_checkequal(intmin(ui32),uint32(0))
assert_checkequal(intmin(ui64),uint64(0))
