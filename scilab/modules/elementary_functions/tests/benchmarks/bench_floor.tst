// Balisc (https://github.com/rdbyk/balisc/)
// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 5000 -->

a1 = rand(1,1);
a2 = rand(3,3);
a3 = rand(10,10);
a4 = rand(100,100);

b1 = a1 + a1*%i;
b2 = a2 + a2*%i;
b3 = a3 + a3*%i;
b4 = a4 + a4*%i;

// <-- BENCH START -->

for i=1:100
 floor(a1);
 floor(b2);
end

for i=1:10
  floor(a2);
  floor(b2);
end

for i=1:3
  floor(a3);
  floor(b3);
end

floor(a4);
floor(b4);

// <-- BENCH END -->
