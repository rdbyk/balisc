// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - SCILAB ENTERPRISES - Simon GARESTE
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

assert_checkerror("h5exists()", [], 77);
assert_checkerror("h5exists(42)", [], 77);
assert_checkerror("h5exists(42,42)", [], 91);
assert_checkerror("h5exists(""42"",42)", [], 91);
assert_checkerror("h5exists(""42"",""42"")", [], 132);

x = 123;
y = 321;
save(TMPDIR + "/xy.sod", "x", "y");
a = h5open(TMPDIR + "/xy.sod", "r");

assert_checkerror("h5exists(a)", [], 77);
assert_checkfalse(h5exists(a,"42"));

b= [%T %T %F];
assert_checkequal(h5exists(a, ["x" "y" "z"]),b);
assert_checkfalse(h5exists(a, "/tmp"));
assert_checktrue(h5exists(a, "/x"));
msgerr = msprintf(gettext("%s: Wrong type for input argument #%d: string expected.\n"), "h5exists", 2);
assert_checkerror("h5exists(a,a.root.x)", [], 91);
c = [%T %T];
assert_checkequal(h5exists(a, "/", ["SCILAB_sod_version", "SCILAB_scilab_version"]),c);
assert_checktrue(h5exists(a, "/x", "SCILAB_Class"));
h5close(a);

assert_checkequal(h5exists(TMPDIR+"/xy.sod", ["x" "y" "z"]),b);
assert_checkfalse(h5exists(TMPDIR+"/xy.sod", "/tmp"));
assert_checktrue(h5exists(TMPDIR+"/xy.sod", "/x"));
c = [%T %T];
assert_checkequal(h5exists(TMPDIR+"/xy.sod", "/", ["SCILAB_sod_version", "SCILAB_scilab_version"]),c);
assert_checktrue(h5exists(TMPDIR+"/xy.sod", "/x", "SCILAB_Class"));
