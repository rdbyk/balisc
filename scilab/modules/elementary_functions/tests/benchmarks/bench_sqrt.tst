// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- BENCH NB RUN : 1000 -->

// <-- BENCH START -->
A = 10*rand(100,100)-5;
B = atan(A);
C = atan(A+A*%i);
// <-- BENCH END -->
