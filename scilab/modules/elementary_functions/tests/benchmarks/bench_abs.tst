// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 2500 -->

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
 abs(a1);
 abs(b2);
end

for i=1:10
  abs(a2);
  abs(b2);
end

for i=1:3
  abs(a3);
  abs(b3);
end

abs(a4);
abs(b4);

// <-- BENCH END -->
