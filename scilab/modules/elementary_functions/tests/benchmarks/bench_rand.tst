// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 1000 -->

// <-- BENCH START -->

for i=1:100
  rand(1,1,'uniform');
  rand(1,1,'normal');
end

for i=1:10
  rand(3,3,'uniform');
  rand(3,3,'normal');
end

for i=1:3
  rand(10,10,'uniform');
  rand(10,10,'normal');

end

rand(100,100,'uniform');
rand(100,100,'normal');

// <-- BENCH END -->
