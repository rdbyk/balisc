// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//

assert_checkequal(swapbytes(1),3.038651941617D-319)
assert_checkequal(swapbytes(3.038651941617D-319),1)

assert_checkequal(swapbytes(int8(27)),int8(27))
assert_checkequal(swapbytes(uint8(27)),uint8(27))

assert_checkequal(swapbytes(int16(1234)),int16(-11772))
assert_checkequal(swapbytes(int16(-11772)),int16(1234))

assert_checkequal(swapbytes(uint16(1234)),uint16(53764))
assert_checkequal(swapbytes(uint16(53764)),uint16(1234))

assert_checkequal(swapbytes(int32(12345678)),int32(1315027968))
assert_checkequal(swapbytes(int32(1315027968)),int32(12345678))

assert_checkequal(swapbytes(uint32(12345678)),uint32(1315027968))
assert_checkequal(swapbytes(uint32(1315027968)),uint32(12345678))

assert_checkequal(swapbytes(int64(12345678)),int64(5648002115885334528))
assert_checkequal(swapbytes(int64(5648002115885334528)),int64(12345678))

assert_checkequal(swapbytes(uint64(12345678)),uint64(5648002115885334528))
assert_checkequal(swapbytes(uint64(5648002115885334528)),uint64(12345678))
