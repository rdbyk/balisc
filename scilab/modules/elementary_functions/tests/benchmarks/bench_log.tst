// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 1000 -->

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
 log(a1);
 log(b1);
 log(c1);
end

for i=1:10
  log(a2);
  log(b2);
  log(c2);
end

for i=1:3
  log(a3);
  log(b3);
  log(c3);
end

log(a4);
log(b4);
log(c4);

// <-- BENCH END -->
