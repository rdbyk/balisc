// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) - 2012 - DIGITEO - Allan CORNET
// Copyright (C) - 2018 - Samuel GOUGEON
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
assert_checkequal(or([]), %F);
assert_checkequal(or(%nan), %T);
assert_checkequal(or([0 %nan]), %T);
assert_checkequal(or(sparse([],[])), %F);
assert_checkequal(or(sparse(%nan)), %T);

A = %T(ones(1, 3));
assert_checkequal(or(A), %T);

A = %F(ones(1, 3));
assert_checkequal(or(A), %F);

A = %T(ones(1, 3));
assert_checkequal(or(A, 'c'), %T);
assert_checkequal(or(A, 2), %T);

REF = [%T %T %T];
assert_checkequal(or(A, 'r'), REF);
assert_checkequal(or(A, 1), REF);

B = (eye(3,3) == 0);
B(1, 1) = %T;
assert_checkequal(or(B), %T);
REF = [%T,%T, %T];
assert_checkequal(or(B, 'r'), REF);
REF = [%T; %T; %T];
assert_checkequal(or(B, 'c'), REF);
