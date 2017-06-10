// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 1000 -->

a1 = 10*(rand(1,1) - 0.5);
a2 = 10*(rand(3,3) - 0.5);
a3 = 10*(rand(10,10) -0.5);
a4 = 10*(rand(100,100) -0.5);

b1 = a1 + a1*%i;
b2 = a2 + a2*%i;
b3 = a3 + a3*%i;
b4 = a4 + a4*%i;

// <-- BENCH START -->

for i=1:100
 exp(a1);
 exp(b2);
end

for i=1:10
  exp(a2);
  exp(b2);
end

for i=1:3
  exp(a3);
  exp(b3);
end

exp(a4);
exp(b4);

// <-- BENCH END -->
