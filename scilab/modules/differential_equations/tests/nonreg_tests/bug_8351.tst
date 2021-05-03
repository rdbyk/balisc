// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 8351 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=8351
//
// <-- Short Description -->
//    The integrate function does not manage the optional input arguments properly.

assert_checkerror("integrate(''sin(x)'',''x'',0)", [], 74);

x = integrate('sin(x)','x',0,%pi);
assert_checkalmostequal(x, 2, [], %eps);

x = integrate('sin(x)','x',0,%pi,1.e-6);
assert_checkalmostequal(x, 2, [], %eps);

x = integrate('sin(x)','x',0,%pi,1.e-6,1);
assert_checkalmostequal(x, 2, [], %eps);
