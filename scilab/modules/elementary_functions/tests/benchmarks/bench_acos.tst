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
 acos(a1);
 acos(b1);
 acos(c1);
end

for i=1:10
  acos(a2);
  acos(b2);
  acos(c2);
end

for i=1:3
  acos(a3);
  acos(b3);
  acos(c3);
end

acos(a4);
acos(b4);
acos(c4);

// <-- BENCH END -->
