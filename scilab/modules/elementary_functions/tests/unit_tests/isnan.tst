// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Samuel GOUGEON
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

assert_checkequal(isnan([]), []);

// With decimal real numbers
// -------------------------
assert_checktrue(isnan(%nan));

M = [%pi %inf -1 %nan 3 -%nan -%inf];
R = [%f %f %f %t %f %t %f];
assert_checkequal(isnan(M), R);
assert_checkequal(isnan(M'),R');
M = sparse(M);
R = sparse(R);
assert_checkequal(isnan(M), R);
assert_checkequal(isnan(M'),R');

M = [%pi %inf -1   %nan
      3 -%nan  0  -%inf];
R = [%f %f %f %t ; %f %t %f %f];
assert_checkequal(isnan(M),R);
M = sparse(M);
R = sparse(R);
assert_checkequal(isnan(M), R);

clear M R
M(:,:,1) = [%pi %inf ; -1  %nan];
M(:,:,2) = [ 3 -%nan ;  0  -%inf];
R(:,:,1) = [%f %f ; %f %t ];
R(:,:,2) = [%f %t ; %f %f ];
assert_checkequal(isnan(M),R);
// no sparse hypermatrix

// With complex numbers
// --------------------
G = [ -%inf -10 0 %nan 10 %inf];
[R,I] = meshgrid(G,G);
C = complex(R,I);
res = [
   0.   0.   0.   0.   0.   0.
   0.   0.   0.   1.   0.   0.
   0.   0.   0.   1.   0.   0.
   0.   1.   1.   1.   1.   0.
   0.   0.   0.   1.   0.   0.
   0.   0.   0.   0.   0.   0.
   ]==1;
assert_checkequal(isnan(C), res);

C = sparse(C);
res = sparse(res);
assert_checkequal(isnan(C), res);
