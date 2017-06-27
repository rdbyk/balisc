// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 10 -->

a1 = string(rand(1,1));
a2 = string(rand(100,1));
a3 = string(rand(1000,1));
a4 = string(rand(10000,1));

// <-- BENCH START -->

for i=1:10000
  execstr(a1);
end

for i=1:100
  execstr(a2);
end

for i=1:10
  execstr(a3);
end

execstr(a4);

// <-- BENCH END -->
