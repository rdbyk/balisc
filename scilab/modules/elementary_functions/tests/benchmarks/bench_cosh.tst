// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 500 -->

a1 = 10*rand(1,1);
a2 = 10*rand(3,3);
a3 = 10*rand(10,10);
a4 = 10*rand(100,100);

b1 = 10*(rand(1,1) - 0.5);
b2 = 10*(rand(3,3) - 0.5);
b3 = 10*(rand(10,10) - 0.5);
b4 = 10*(rand(100,100) - 0.5);

c1 = a1 + a1*%i;
c2 = a2 + a2*%i;
c3 = a3 + a3*%i;
c4 = a4 + a4*%i;

// <-- BENCH START -->

for i=1:100
 cosh(a1);
 cosh(b1);
 cosh(c1);
end

for i=1:10
  cosh(a2);
  cosh(b2);
  cosh(c2);
end

for i=1:3
  cosh(a3);
  cosh(b3);
  cosh(c3);
end

cosh(a4);
cosh(b4);
cosh(c4);

// <-- BENCH END -->
