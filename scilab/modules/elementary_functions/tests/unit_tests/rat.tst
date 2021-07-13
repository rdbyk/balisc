// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
// Copyright (C) 2012 - Scilab Enterprises - Cedric Delamarre
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// by reference
[n, d] = rat(%pi);
assert_checkequal(n, 355);
assert_checkequal(d, 113);

y = rat(%pi);
assert_checkalmostequal(y, n/d, [], 2*%eps);

[n, d] = rat(%pi, 1.d-12);
assert_checkequal(n, 1146408);
assert_checkequal(d, 364913);

// by value
[n, d] = rat(3.1415927);
assert_checkequal(n, 355);
assert_checkequal(d, 113);

y = rat(%pi);
assert_checkalmostequal(y, n/d, [], 2*%eps);

[n, d] = rat(3.1415927, 1.d-12);
assert_checkequal(n, 1640169);
assert_checkequal(d, 522082);
