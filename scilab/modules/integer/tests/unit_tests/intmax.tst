// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Unit test "intmax" -->

assert_checkequal(intmax(),int32(2147483647)) // default 'int32'

assert_checkequal(intmax('int8'),int8(127))
assert_checkequal(intmax('int16'),int16(32767))
assert_checkequal(intmax('int32'),int32(2147483647))
assert_checkequal(intmax('int64'),int64(2)^63-1)

assert_checkequal(intmax('uint8'),uint8(255))
assert_checkequal(intmax('uint16'),uint16(65535))
assert_checkequal(intmax('uint32'),uint32(4294967295))
assert_checkequal(intmax('uint64'),uint64(2)^64-1)

si8=int8(-1)
si16=int16(3)
si32=int32(-5)
si64=int64(7)
ui8=uint8(2)
ui16=uint16(4)
ui32=uint32(6)
ui64=uint64(8)

assert_checkequal(intmax(si8),int8(127))
assert_checkequal(intmax(si16),int16(32767))
assert_checkequal(intmax(si32),int32(2147483647))
assert_checkequal(intmax(si64),int64(2)^63-1)

assert_checkequal(intmax(ui8),uint8(255))
assert_checkequal(intmax(ui16),uint16(65535))
assert_checkequal(intmax(ui32),uint32(4294967295))
assert_checkequal(intmax(ui64),uint64(2)^64-1)
