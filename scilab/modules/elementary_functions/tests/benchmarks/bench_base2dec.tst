// Balisc (https://github.com/rdbyk/balisc/)
// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 1 -->

a1 = dec2hex(ceil(15*rand(20,20)));
a2 = dec2hex(ceil(1023*rand(20,20)));
a3 = dec2hex(ceil(4095*rand(20,20)));
a4 = dec2hex(ceil(65535*rand(20,20)));

// <-- BENCH START -->

for i=1:4096
  base2dec(a1,16);
end

for i=1:256
  base2dec(a2,16);
end

for i=1:16
  base2dec(a3,16);
end

base2dec(a4,16);

// <-- BENCH END -->
