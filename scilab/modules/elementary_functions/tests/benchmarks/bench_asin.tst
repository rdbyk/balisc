// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 500 -->

a1 = 2*(rand(1,1) - 0.5);
a2 = 2*(rand(3,3) - 0.5);
a3 = 2*(rand(10,10) - 0.5);
a4 = 2*(rand(100,100) - 0.5);

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
 asin(a1);
 asin(b1);
 asin(c1);
end

for i=1:10
  asin(a2);
  asin(b2);
  asin(c2);
end

for i=1:3
  asin(a3);
  asin(b3);
  asin(c3);
end

asin(a4);
asin(b4);
asin(c4);

// <-- BENCH END -->
