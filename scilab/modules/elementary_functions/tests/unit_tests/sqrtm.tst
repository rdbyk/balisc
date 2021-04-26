// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Paul Bignier
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

assert_checkalmostequal(sqrtm([8 8 ; 8 8]), [2 2 ; 2 2]);

x = [0 1; 2 4];
w = sqrtm(x);
assert_checkalmostequal(norm(w*w-x), 0, [], 7*%eps);
x(1, 2) = %i;
w = sqrtm(x);
assert_checkalmostequal(norm(w*w-x, 1), 0, [], 15*%eps);


// Error checks
assert_checkerror("sqrtm(list())", [], 95);
assert_checkerror("sqrtm(%s)", [], 95);
assert_checkerror("sqrtm(%t)", [], 95);

assert_checkerror("sqrtm([1 2 3; 4 5 6])", [], 103);
assert_checkerror("sqrtm([1 2; 3 4; 5 6])", [], 103);
