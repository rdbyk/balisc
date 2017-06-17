// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 500 -->

a1 = 100*(rand(1,1) - 0.5);
a2 = 100*(rand(3,3) - 0.5);
a3 = 100*(rand(10,10) - 0.5);
a4 = 100*(rand(100,100) - 0.5);

// <-- BENCH START -->

for i=1:100
  nearfloat("succ",a1);
  nearfloat("pred",a1);
end

for i=1:10
  nearfloat("succ",a2);
  nearfloat("pred",a2);
end

for i=1:3
  nearfloat("succ",a3);
  nearfloat("pred",a3);
end

nearfloat("succ",a4);
nearfloat("pred",a4);

// <-- BENCH END -->
