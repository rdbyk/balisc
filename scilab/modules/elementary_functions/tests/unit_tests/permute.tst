// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Paul Bignier
// Copyright (C) 2016 - Samuel GOUGEON
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// With a real matrix
x = [1 2 3; 4 5 6];
y = permute(x, [2 1]);
assert_checkequal(y, x');

// With an integer matrix
x = int32(x);
y = permute(x, [2 1]);
assert_checkequal(y, x');

// With a string matrix
x = string(x);
y = permute(x, [2 1]);
assert_checkequal(y, x');

// With a complex matrix
x = [1 2 3; 4 5 6]*%i;
y = permute(x, [2 1]);
refY = [1 4; 2 5; 3 6]*%i;
assert_checkequal(y, refY);

// With a real hypermatrix
x0 = matrix(1:12, [2, 3, 2]);
y = permute(x0, [3 1 2]);
clear refY
refY(:, :, 1) = [1 2; 7 8];
refY(:, :, 2) = [3 4; 9 10];
refY(:, :, 3) = [5 6; 11 12];
refY0 = refY;
assert_checkequal(y, refY);

// With a boolean hypermatrix
x = x0<5;
y = permute(x, [3 1 2]);
refY = refY0<5;
assert_checkequal(y, refY);

// With an integer hypermatrix
x = int32(x0);
y = permute(x, [3 1 2]);
refY = int32(refY0);
assert_checkequal(y, refY);

// With a string hypermatrix
x = string(x0);
y = permute(x, [3 1 2]);
refY = string(refY0);
assert_checkequal(y, refY);

// With a complex hypermatrix
x = x0*%i;
y = permute(x, [3 1 2]);
refY = refY0*%i;
assert_checkequal(y, refY);

// With an hypermatrix of polynomials
x = 1 + x0*%z;
y = permute(x, [3 1 2]);
refY = 1 + refY0*%z;
assert_checkequal(y, refY);

// With an hypermatrix of rationals
x = (1 + x0*%z)./(1 - x0*%z);
y = permute(x, [3 1 2]);
refY = (1 + refY0*%z) ./ (1 - refY0*%z);
assert_checkequal(y, refY);

// With an array of structures
s(3,4,2).r = %pi;
ss = size(s);
ps = permute(s,[2 3 1]);
assert_checkequal(size(ps),ss([2 3 1]));
assert_checkequal(ps(24).r, %pi);

// Error checks
// ------------
msg = _("%s: Wrong value for input argument #%d: Must be a valid permutation of [1..n>%d] integers.\n");
refMsg = msprintf(msg, "permute", 2, 2);
assert_checkerror("permute(x, [1 2]);", refMsg);
assert_checkerror("permute(x, [1 2 4]);", refMsg);
assert_checkerror("permute(x, [1 3.1 2]);", refMsg);
assert_checkerror("permute(x, [1 2 3 5]);", refMsg);
