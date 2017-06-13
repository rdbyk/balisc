// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 500 -->

a1 = 10*(rand(1,1) - 0.5);
a2 = 10*(rand(3,3) - 0.5);
a3 = 10*(rand(10,10) - 0.5);
a4 = 10*(rand(100,100) - 0.5);

b1 = a1 + a1*%i;
b2 = a2 + a2*%i;
b3 = a3 + a3*%i;
b4 = a4 + a4*%i;

// <-- BENCH START -->

for i=1:100
 cos(a1);
 cos(b1);
end

for i=1:10
  cos(a2);
  cos(b2);
end

for i=1:3
  cos(a3);
  cos(b3);
end

cos(a4);
cos(b4);

// <-- BENCH END -->
