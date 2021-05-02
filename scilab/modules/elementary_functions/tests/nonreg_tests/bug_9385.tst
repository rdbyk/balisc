// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 9385 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=9385
//
// <-- Short Description -->
//    The type checking in trigonometric functions has been added
// =============================================================================

assert_checkfalse(execstr("tanm(""x"")"   ,"errcatch") == 0);
refMsg = msprintf(_("%s: Wrong type for input argument #%d: Real or complex matrix expected.\n"), "tanm", 1);
assert_checkerror("tanm(""x"")", refMsg);

assert_checkerror("tanhm(""x"")", [], 95);

assert_checkfalse(execstr("tanh(""x"")"   ,"errcatch") == 0);
refMsg = [msprintf(_("Function not defined for given argument type(s),\n"));msprintf(_("check arguments or define function %s for overloading.\n"), "%c_tanh")];
assert_checkerror("tanh(""x"")", refMsg);

assert_checkerror("tand(""x"")", [], 94);
assert_checkerror("sind(""x"")", [], 94);
assert_checkerror("sinc(""x"")", [], 90);
assert_checkerror("sech(""x"")", [], 95);
assert_checkerror("secd(""x"")", [], 94);
assert_checkerror("sec(""x"")", [], 95);
assert_checkerror("csgn(""x"")", [], 95);
assert_checkerror("csch(""x"")", [], 95);
assert_checkerror("cscd(""x"")", [], 94);
assert_checkerror("csc(""x"")", [], 95);
assert_checkerror("cotd(""x"")", [], 94);
assert_checkerror("cosd(""x"")",  [], 94);
assert_checkerror("atand(""x"")", [], 94);
assert_checkerror("atand(1, ""x"")", [], 94);
assert_checkerror("asind(""x"")", [], 94);
assert_checkerror("asech(""x"")", [], 95);
assert_checkerror("asecd(""x"")", [], 95);
assert_checkerror("asec(""x"")", [], 95);
assert_checkerror("acsch(""x"")", [], 95);
assert_checkerror("acscd(""x"")", [], 94);
assert_checkerror("acsc(""x"")", [], 94);
assert_checkerror("acoth(""x"")", [], 94);
assert_checkerror("acotd(""x"")", [], 94);
assert_checkerror("acot(""x"")", [], 94);
assert_checkerror("acosd(""x"")", [], 94);
