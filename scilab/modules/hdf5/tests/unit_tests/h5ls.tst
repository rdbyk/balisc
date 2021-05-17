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

assert_checkerror("h5ls()", [], 77);
assert_checkerror("h5ls(42)", [], 91);
assert_checkerror("h5ls(""42"")", [], 132);

x = int8(matrix(1:80, 10, 8));
save(TMPDIR + "/x.sod", "x");


assert_checkerror("h5ls(""x"")", [], 132);

assert_checkerror("h5ls(TMPDIR+""/x.sod"",12.0)", [], 91);
assert_checkerror("h5ls(TMPDIR+""/x.sod"",""."",12.0)", [], 91);

a = h5open(TMPDIR + "/x.sod");
dset = ["x" "dataset"];
attr = ["SCILAB_scilab_version" "attribute";"SCILAB_sod_version" "attribute"];
assert_checkequal(h5ls(a),cat(1,dset,attr));
attr = ["SCILAB_Class" "attribute";"SCILAB_precision" "attribute"];
assert_checkequal(h5ls(a.root.x),attr);
assert_checkequal(h5ls(a,"/x"),attr);

attr = ["SCILAB_scilab_version";"SCILAB_sod_version"];
assert_checkequal(h5ls(a,".","a"),attr);

assert_checkerror("h5ls(a,""."",""x"")", [], 132);

assert_checkerror("h5ls(12.0)", [], 91);
assert_checkerror("h5ls(a,12.0)", [], 91);
assert_checkerror("h5ls(a,""."",12.0)", [], 91);
assert_checkerror("h5ls(""x"")", [], 132);

h5close(a);

attr = ["SCILAB_scilab_version" "attribute";"SCILAB_sod_version" "attribute"];
assert_checkequal(h5ls(TMPDIR+"/x.sod"),cat(1,dset,attr));
attr = ["SCILAB_Class" "attribute";"SCILAB_precision" "attribute"];
assert_checkequal(h5ls(TMPDIR+"/x.sod","/x"),attr);
attr = ["SCILAB_scilab_version";"SCILAB_sod_version"];
assert_checkequal(h5ls(TMPDIR+"/x.sod",".","a"),attr);
