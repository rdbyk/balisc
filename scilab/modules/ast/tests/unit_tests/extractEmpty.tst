// ============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Antoine ELIAS
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// ============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

a = [];
assert_checkequal(a(5), a);
assert_checkequal(a(:), a);
assert_checkequal(a(1:2), a);
assert_checkequal(a(:,:), a);
assert_checkequal(a(1:2,1:2), a);
assert_checkequal(a(%t), a);
assert_checkequal(a(%f), a);

a = {};
assert_checkequal(a(5), a);
assert_checkequal(a(:), a);
assert_checkequal(a(1:2), a);
assert_checkequal(a(:,:), a);
assert_checkequal(a(1:2,1:2), a);
assert_checkequal(a(%t), a);
assert_checkequal(a(%f), a);

a = struct();
assert_checkequal(a(5), a);
assert_checkequal(a(:), a);
assert_checkequal(a(1:2), a);
assert_checkequal(a(:,:), a);
assert_checkequal(a(1:2,1:2), a);
assert_checkequal(a(%t), a);
assert_checkequal(a(%f), a);

a = ones(5,5);
assert_checkequal(a(), a);

a = {1,2;3,4};
assert_checkequal(a{}, list(1,3,2,4));

a = struct();
assert_checkequal(a(), a);
