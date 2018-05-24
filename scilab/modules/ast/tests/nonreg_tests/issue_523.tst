// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for issue 523 -->
//
// <-- Github URL -->
// https://github.com/rdbyk/balisc/issues/523
//
// <-- Short Description -->
// Relational Ops (<, <=,>, >=) on "eye()" may yield No, Wrong, or Corrupted Results

ONES = ones(2,2);

assert_checkequal(eye() < 1, %f)
assert_checkequal(1 < eye(), %f)

assert_checkequal(eye() < ONES, [%f,%t;%t,%f])
assert_checkequal(ONES < eye(), [%f,%f;%f,%f])

assert_checkequal(eye() <= 1, %t)
assert_checkequal(1 <= eye(), %t)

assert_checkequal(eye() <= ONES, [%t,%t;%t,%t])
assert_checkequal(ONES <= eye(), [%t,%f;%f,%t])

assert_checkequal(eye() > 1, %f)
assert_checkequal(1 > eye(), %f)

assert_checkequal(eye() > ONES, [%f,%f;%f,%f])
assert_checkequal(ONES > eye(), [%f,%t;%t,%f])

assert_checkequal(eye() >= 1, %t)
assert_checkequal(1 >= eye(), %t)

assert_checkequal(eye() >= ONES, [%t,%f;%f,%t])
assert_checkequal(ONES >= eye(), [%t,%t;%t,%t])
