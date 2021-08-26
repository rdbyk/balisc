// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2019 - Stéphane MOTTELET
// Copyright (C) 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH GRAPHIC -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

// <-- Non-regression test for bug 15995 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=15995
//
// <-- Short Description -->
// Missing patch in surface plot (regression)

surf(0:1,0:1,[0 1;1 %eps]);
f1=gcf();

scf(1);
surf(0:1,0:1,[0 1;1 0]);
f2=gcf();

assert_checkalmostequal(f1.children.children.data.x,f2.children.children.data.x, [], 3*%eps);
assert_checkalmostequal(f1.children.children.data.y,f2.children.children.data.y, [], 3*%eps);
assert_checkalmostequal(f1.children.children.data.z,f2.children.children.data.z, [], 3*%eps);
