// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH GRAPHIC -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

// <-- Non-regression test for bug 8640 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=8640
//
// <-- Short Description -->
//    The histplot function has failed when the data vector contains the same values
// =============================================================================
clf();
histplot(2, [2 2 2 2 2]);
a = gca();
x = a.children(1).children.data;
y = [2*%eps; 1; 1; 0; 0; 0; %eps];
assert_checkalmostequal(y, x(:,2), [], 200 * %eps);
