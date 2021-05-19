// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - SCILAB ENTERPRISES - Simon GARESTE
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

assert_checkerror("h5mv()", [], 77);
assert_checkerror("h5mv(42,42)", [], 91);
assert_checkerror("h5mv(""42"",42)", [], 74);
assert_checkerror("h5mv(""42"",42,42)", [], 91);
assert_checkerror("h5mv(""42"",""42"",42)", [], 91);
assert_checkerror("h5mv(""42"",""42"",""42"")", [], 132);

deletefile(TMPDIR + "/test.h5");
deletefile(TMPDIR + "/test1.h5");
deletefile(TMPDIR + "/test2.h5");

a = h5open(TMPDIR + "/test.h5");

assert_checkerror("h5mv(a,""42"",""42"")", [], 132);
assert_checkerror("h5mv(a,""42"",a)", [], 132);

b = h5open(TMPDIR + "/test1.h5");

c = h5open(TMPDIR + "/test2.h5");
h5group(a, "Grp_1");
h5write(a.root.Grp_1, "Dset_1", [1 2 ; 3 4]);
h5flush(a);
h5group(b, "BGrp");
h5write(b("/BGrp"), "BDset", 11:18);
h5close(b)
h5group(c,"CGrp");
h5write(c("/CGrp"),"CDset",(8:12)')
h5close(c);

assert_checkerror("h5mv(a.root.Grp_1,TMPDIR+""/test12.h5"",""/mnt"")", [], 132);

h5mv(a.root.Grp_1, "Dset_1", a, "Dset_2")
assert_checkequal(a.root.Datasets,"Dset_2");
assert_checkequal(a.root.Dset_2.data,[1 2;3 4]);

assert_checkerror("h5mv(a,a)", [], 132);
assert_checkerror("h5mv(a,12.0)", [], 74);
assert_checkerror("h5mv(12.0,a)", [], 91);
assert_checkerror("h5mv(a,d)", [], 40);
assert_checkerror("h5mv(a,c)", [], 130);
assert_checkerror("h5mv(a,""d"")", [], 74);

h5mv(TMPDIR  +"/test1.h5", "/BGrp/BDset", a.root.Grp_1)
assert_checkequal(a.root.Grp_1.BDset.data,(11:18));
assert_checkequal(a.root.Datasets,"Dset_2");
h5close(a);

h5mv(TMPDIR+"/test.h5","/Grp_1",TMPDIR+"/test1.h5","/grp2");
assert_checkequal(h5ls(TMPDIR+"/test1.h5"),["BGrp" "group";"grp2" "group"]);
a=h5open(TMPDIR+"/test.h5","a");
msgerr = msprintf(gettext("%s: Error in retrieving field content:\n%s\n"), "%H5Object_e", msprintf(gettext("Invalid field: %s"), "Group_1"));
assert_checkerror("h5ls(a.root.Group_1)",msgerr,999);
assert_checkequal(h5ls(TMPDIR+"/test1.h5"),["BGrp" "group" ; "grp2" "group"]);
