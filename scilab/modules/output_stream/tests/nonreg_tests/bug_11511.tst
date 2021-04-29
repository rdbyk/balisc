// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Charlotte HECQUET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 11511 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/11511
//
// <-- Short Description -->
// Error does not accept string matrix

myLongString=["azea";"bc";"fdgdf"]; 
function f();
    error(myLongString);
endfunction

assert_checkerror("f()", myLongString);
