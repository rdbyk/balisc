// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//

assert_checkequal(typecast(1,'int8'),int8([0 0 0 0 0 0 -16 63]))
assert_checkequal(typecast(1,'int16'),int16([0 0 0 16368]))
assert_checkequal(typecast(1,'int32'),int32([0 1072693248]))
assert_checkequal(typecast(1,'int64'),int64(4607182418800017408))

assert_checkequal(typecast(-1,'uint8'),uint8([0 0 0 0 0 0 240 191]))
assert_checkequal(typecast(-1,'uint16'),uint16([0 0 0 49136]))
assert_checkequal(typecast(-1,'uint32'),uint32([0 3220176896]))
assert_checkequal(typecast(-1,'uint64'),uint64(13830554455654793216))

assert_checkequal(typecast(int64(4607182418800017408),'double'),1)
assert_checkequal(typecast(int64(4607182418800017408),'int32'),int32([0 1072693248]))
assert_checkequal(typecast(int64(4607182418800017408),'int16'),int16([0 0 0 16368]))
assert_checkequal(typecast(int64(4607182418800017408),'int8'),int8([0 0 0 0 0 0 -16 63]))

assert_checkequal(typecast(uint64(13830554455654793216),'double'),-1)
assert_checkequal(typecast(uint64(13830554455654793216),'uint32'),uint32([0 3220176896]))
assert_checkequal(typecast(uint64(13830554455654793216),'uint16'),uint16([0 0 0 49136]))
assert_checkequal(typecast(uint64(13830554455654793216),'uint8'),uint8([0 0 0 0 0 0 240 191]))

assert_checkequal(typecast(int8([0 0 0 0 0 0 -16 63]),'int8'),int8([0 0 0 0 0 0 -16 63]))

assert_checkequal(typecast(typecast(int8([1,2;3,4])','int8'),'int8'),int8([1;2;3;4]))

assert_checkequal(typecast([],'uint64'),[])
