// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

// <-- Non-regression test for bug 13470 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=13740
//
// <-- Short Description -->
//    histplot(0,0,%t) crashed.
// =============================================================================

errmsg=msprintf(_("%s: Argument #%d: non-zero decimal integer expected.\n"),"histc",2);
assert_checkerror("histplot(0,0,%t)", errmsg);
