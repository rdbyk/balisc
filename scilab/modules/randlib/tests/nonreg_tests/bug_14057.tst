// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 14057 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=14057
//
// <-- Short Description -->
//    Calling grand(m,n) returned a wrong error and grand(m,n,p) called %s_grand
//    function instead of an error.
// =============================================================================

assert_checkerror("grand(2,3)", [], 91);
assert_checkerror("grand(4,3,2)", [], 91);
