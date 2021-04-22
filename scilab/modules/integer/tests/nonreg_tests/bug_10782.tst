// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// ===========================================================================

// <-- Non-regression test for bug 10782 -->
//
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=10782
//
// <-- Short Description -->
// iconvert did not check input arguments


// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

B = 69;

b = int32([1 -120 127 312]);
REF = int8([1 -120 127 312]);
y = iconvert(b, 1);
assert_checkequal(y, REF);

y = iconvert(B, 0); // double
assert_checkequal(type(y), 1);
assert_checkequal(typeof(y), "constant");

y = iconvert(B, 1); // int8
assert_checkequal(type(y), 8);
assert_checkequal(typeof(y), "int8");

y = iconvert(B, 2); // int16
assert_checkequal(type(y), 8);
assert_checkequal(typeof(y), "int16");

y = iconvert(B, 4); // int32
assert_checkequal(type(y), 8);
assert_checkequal(typeof(y), "int32");

y = iconvert(B, 11); // uint8
assert_checkequal(type(y), 8);
assert_checkequal(typeof(y), "uint8");

y = iconvert(B, 12); // uint16
assert_checkequal(type(y), 8);
assert_checkequal(typeof(y), "uint16");

y = iconvert(B, 14); // uint32
assert_checkequal(type(y), 8);
assert_checkequal(typeof(y), "uint32");

y = iconvert(%i, 0); // only real part is converted to double
assert_checkequal(type(y), 1);
assert_checkequal(typeof(y), "constant");

assert_checkerror ("y = iconvert(B, 20);", [], 110);
assert_checkerror ("y = iconvert(B, 0.1);", [], 110);
assert_checkerror ("y = iconvert(B, [0 1]);", [], 110);
