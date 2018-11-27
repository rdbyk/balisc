// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

//<-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 7958 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=7958
//
// <-- Short Description -->
//  mrfit did not allow a fourth parameter as shown in the help page.

w=0.01:0.01:2;
s=poly(0,"s");
G=syslin("c",2*(s^2+0.1*s+2),(s^2+s+1)*(s^2+0.3*s+1)); // syslin('c',Num,Den);
fresp=repfreq(G,w);
mag=abs(fresp);
Gid=mrfit(w,mag,4);
Gidd = mrfit(w, mag, 4, ones(length(w), 1));
assert_checkalmostequal(coeff(Gidd.num), coeff(Gid.num), 1e-14);
assert_checkalmostequal(coeff(Gidd.den), coeff(Gid.den), 1e-14);

// error
assert_checkfalse(execstr("mrfit(w, mag, 4, 1)"   ,"errcatch") == 0);
refMsg = msprintf(_("%s: Arguments #%d and #%d: Same numbers of elements expected.\n"), "mrfit", 1, 4);
assert_checkerror("mrfit(w, mag, 4, 1)", refMsg);

assert_checkfalse(execstr("mrfit(w, mag, 4, ones(1, length(w)))"   ,"errcatch") == 0);
refMsg = msprintf(_("%s: Argument #%d: Column expected.\n"), "mrfit", 4);
assert_checkerror("mrfit(w, mag, 4, ones(1, length(w)))", refMsg);
