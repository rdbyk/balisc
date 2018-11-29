// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2018 - ESI-Group - Adeline CARNIS
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 15363 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=15363
//
// <-- Short Description -->
// `h2norm()` could no longer be applied to undefined time domain systems, and 
// made the residu() right example failing.

s = poly(0,'s');
H = [s/(s+1)^2,1/(s+2)];N=H.num;D=H.den;
w = residu(N.*horner(N,-s),D,horner(D,-s));  //N(s) N(-s) / D(s) D(-s)
assert_checkalmostequal(sqrt(sum(w)), h2norm(tf2ss(H)));
