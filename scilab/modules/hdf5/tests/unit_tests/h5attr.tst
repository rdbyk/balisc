// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - SCILAB ENTERPRISES - Simon GARESTE
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

assert_checkerror("h5attr()", [], 77);
assert_checkerror("h5attr(42)", [], 77);
assert_checkerror("h5attr(42,42,42,42)", [],90);
assert_checkerror("h5attr(""42"",42,42,42)", [], 91);
assert_checkerror("h5attr(""42"",""42"",42,42)", [], 91);
assert_checkerror("h5attr(""42"",""42"",""42"",42)", [], 132);

x = 1:5 + %pi;
save(TMPDIR + "/x.sod", "x");
a = h5open(TMPDIR + "/x.sod");

assert_checkerror("h5attr(a,""42"",""42"",42)", [], 132);

h5attr(a, ".", "My Attribute", int8(123));
assert_checkequal(a.root("My Attribute").Data,int8(123));
assert_checkerror("h5attr(a, ""."", ""My Attribute"", %pi)", [], 132);
assert_checkerror("h5attr(a,""."",a.root.Attributes,int8(2))", [], 91);

h5group(a,"Group_1");
h5attr(a,"/Group_1","New",[5 6]);
assert_checkequal(a.root.Group_1.New.Data,[5 6]);
h5write(a,"Group_1/Dset_1",[1 2;3 4]);
h5attr(a,"Group_1/Dset_1","Second",[7 8]);
assert_checkequal(a.root.Group_1.Dset_1.Second.Data,[7 8]);

assert_checkerror("h5attr(TMPDIR+""/y.sod"",""."",""New"",int8(16))", [], 132);
h5attr(TMPDIR+"/x.sod", ".", "New", int8(8));
assert_checkequal(a.root.New.Data,int8(8));


h5attr(a, "/x", "My Dataset Attribute", int16(321));
h5close(a);

// h5writeattr testing
x = 1:5 + %pi;
save(TMPDIR + "/x.sod", "x");
a = h5open(TMPDIR + "/x.sod");
h5writeattr(a, ".", "My Attribute", int8(123));
assert_checkequal(a.root("My Attribute").Data,int8(123));
assert_checkerror("h5writeattr(a, ""."", ""My Attribute"", %pi)", [], 132);
assert_checkerror("h5writeattr(a,""."",a.root.Attributes,int8(2))", [], 91);

h5group(a,"Group_1");
h5writeattr(a,"/Group_1","New",[5 6]);
assert_checkequal(a.root.Group_1.New.Data,[5 6]);
h5write(a,"Group_1/Dset_1",[1 2;3 4]);
h5writeattr(a,"Group_1/Dset_1","Second",[7 8]);
assert_checkequal(a.root.Group_1.Dset_1.Second.Data,[7 8]);

assert_checkerror("h5writeattr(TMPDIR+""/y.sod"",""."",""New"",int8(16))", [], 132);
h5attr(TMPDIR+"/x.sod", ".", "New", int8(8));
assert_checkequal(a.root.New.Data,int8(8));

h5writeattr(a, "/x", "My Dataset Attribute", int16(321));
h5close(a);
