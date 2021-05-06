// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - INRIA - Serge Steer
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 9675 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=9675
//
// <-- Short Description -->
// iir returns wrong value with  Scilab-5.3.1 and Scilab-5.3.2 under Windows_64

hz=iir(3,'bp','cheb1',[.15 .25],[.08 .03]);
z=poly(0,'z');
num=-0.013202009223+0.039606027668*z^2-0.039606027668*z^4+ ..
    0.013202009223*z^6;
den=0.500720867559-1.032666480454*z+2.407044124849*z^2 ..
    -2.614123854577*z^3+3.000398199872*z^4-1.647252234036*z^5+z^6;

assert_checkalmostequal (coeff(hz.num) , coeff(num) , 1d-10);
