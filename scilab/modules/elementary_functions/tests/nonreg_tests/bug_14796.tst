// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 14796 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=14796
//
// <-- Short Description -->
//    ind2sub(dims, []) returns now [].

res = ind2sub([4 2], []);
expected = [];
assert_checkequal(res, expected);

res = ind2sub([4 2 5], []);
assert_checkequal(res, expected);

assert_checkerror("[resi, resj] = ind2sub([4 2], [])", [], 81);
