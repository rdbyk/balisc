// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2020 - Samuel GOUGEON
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->

// <-- Non-regression test for bug 4171 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/4171
//
// <-- Short Description -->
// A list including some structures was wrongly displayed

// Bug 4171
// --------
stru.field = "value";

// Add this struct in a tlist
tl1 = tlist("X", stru);
tl2 = tlist("X", tl1, tl1)

// Same beahviour with a list
l1 = list(stru);
l2 = list(l1, l1)

// Bug 11484 (duplicate)
// ---------
x = struct('a',4,'b',3);
y = struct('a',5,'b',6);
z = struct('a',7,'b',2);

list_c = list();
list_c(0) = list(x,y);
list_c(0) = list(z)
