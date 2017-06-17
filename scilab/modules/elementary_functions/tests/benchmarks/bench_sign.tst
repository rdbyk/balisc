// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 2000 -->

a1 = rand(1,1) - 0.5;
a2 = rand(3,3) - 0.5;
a3 = rand(10,10) -0.5;
a4 = rand(100,100) -0.5;

b1 = a1 + a1*%i;
b2 = a2 + a2*%i;
b3 = a3 + a3*%i;
b4 = a4 + a4*%i;

// <-- BENCH START -->

for i=1:100
 sign(a1);
 sign(b1);
end

for i=1:10
  sign(a2);
  sign(b2);
end

for i=1:3
  sign(a3);
  sign(b3);
end

sign(a4);
sign(b4);

// <-- BENCH END -->
