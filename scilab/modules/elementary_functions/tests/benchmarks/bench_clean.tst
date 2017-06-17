// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 2000 -->

a1 = rand(1,1) - 0.5;
a2 = rand(3,3) - 0.5;
a3 = rand(10,10) - 0.5;
a4 = rand(100,100) - 0.5;

b1 = a1 + a1*%i;
b2 = a2 + a2*%i;
b3 = a3 + a3*%i;
b4 = a4 + a4*%i;

// <-- BENCH START -->
for i=1:100
 clean(a1,0.1,0.1);
 clean(b1,0.1,0.1);
end

for i=1:10
 clean(a2,0.1,0.1);
 clean(b2,0.1,0.1);
end

for i=1:3
 clean(a3,0.1,0.1);
 clean(b3,0.1,0.1);
end

clean(a4,0.1,0.1);
clean(b4,0.1,0.1);

// <-- BENCH END -->
