// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

A = [ 2.   3.   8.
      7.   6.   6.
      0.   6.   8. ];

B = [  6.   72.
      56.   19.
      66.   54. ];

poles = [-3 -2 -1];

K  = [ 0.044710786917411   0.089632805898998   0.061019918506323
       0.126834604574456  -0.004550582679784   0.067395427190544 ];
       
assert_checkalmostequal(ppol(A,B,poles), K, 100*%eps);
