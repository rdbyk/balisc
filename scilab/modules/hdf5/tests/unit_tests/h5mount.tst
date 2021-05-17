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

assert_checkerror("h5mount()", [], 77);
assert_checkerror("h5mount(42)", [], 77);
assert_checkerror("h5mount(42,42,42)", [], 90);

a = h5open(TMPDIR + "/test.h5", "w");

assert_checkerror("h5mount(a,""42"",42)", [], 90);

h5group(a, "/mnt");
b = h5open(TMPDIR + "/test1.h5", "w");
h5group(b, "Group_1");
h5write(b, "Group_1/Dataset_1", uint32([1 2;3 4]));
c = h5open(TMPDIR + "/test2.h5", "w");
h5group(c, "Group_2");
h5write(c, "Group_2/Dataset_2", uint32([14 15 16;17 18 19]));

h5mount(a, "/mnt", b);
assert_checkequal(a.root.mnt.Groups,"Group_1");
assert_checkerror("h5mount(a, ""/mnt"", b)", [], 132);
h5mount(a, "/mnt", c);
assert_checkequal(a.root.mnt.Groups,"Group_2");
assert_checkerror("h5mount(a,""/test"",c)", [], 132);
msgerr = msprintf(gettext("%s: Error in retrieving field content:\n%s\n"), "%H5Object_e", msprintf(gettext("Invalid field: %s"), "Group_1"));
assert_checkerror("h5write(a.root.mnt.Group_1, ""Dataset_1"", uint32([10 11;12 13]))",msgerr,999);
msgerr = msprintf(gettext("%s: %s\n"), "h5write", gettext("Cannot write data in the dataset."));
msgerr($+1) = gettext("HDF5 description") + ": " + "src and dest dataspaces have different number of elements selected.";
assert_checkerror("h5write(a.root.mnt.Group_2, ""Dataset_2"", uint32([10 11;12 13]))",msgerr,999);
h5write(a.root.mnt.Group_2, "Dataset_2", uint32([10 11 2;12 13 9]));
h5umount(a, "/mnt");
assert_checkequal(a.root.mnt.Groups,"Group_1");
assert_checkequal(c.root.Group_2.Dataset_2.data,uint32([10 11 2;12 13 9]));
h5rm(a, "/mnt")
assert_checkequal(c.root.Group_2.Dataset_2.data,uint32([10 11 2;12 13 9]));
h5close(a, b, c)
assert_checkequal(h5read(TMPDIR+"/test2.h5","/Group_2/Dataset_2"),uint32([10 11 2;12 13 9]));
