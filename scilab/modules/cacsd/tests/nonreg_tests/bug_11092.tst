// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - INRIA - Serge Steer
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=11092 
//
// <-- Short Description -->
// Incorrect argument check in h_inf

G=syslin("c",1/%s^3);
[P,r]=macglov(G);
assert_checktrue(execstr("[K,ro]=h_inf(P,r,0,1,30)","errcatch")==0); 
