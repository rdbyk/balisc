// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 2500 -->

A = 10*rand(100,100)+0.1;

a1 = 10*rand(1,1) + 0.1;
a2 = 10*rand(3,3) + 0.1;
a3 = 10*rand(10,10) + 0.1;
a4 = 10*rand(100,100) + 0.1;

// <-- BENCH START -->

for i=1:100
 log1p(a1);
end

for i=1:10
  log1p(a2);
end

for i=1:3
  log1p(a3);
end

log1p(a4);

// <-- BENCH END -->
