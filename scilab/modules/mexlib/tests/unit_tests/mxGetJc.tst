// ============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2017-2017 - Gsoc 2017 - Siddhartha Gairola
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// ============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

cd(TMPDIR);
ilib_verbose(0);
mputl(["#include ""mex.h""";
"void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])";
"{";
"    int ndim = 3;";
"    int *jc = mxGetJc(prhs[0]);";
"    mxArray *ptr = mxCreateNumericMatrix(1, ndim, mxINT32_CLASS, mxREAL);";
"    mxSetData(ptr, jc);";
"    plhs[0] = ptr;";
"}"],"mexgetJc.c");
ilib_mex_build("libmextest",["getJc","mexgetJc","cmex"], "mexgetJc.c",[]);
exec("loader.sce");


sp1 = sparse([1 2 3]);
sp2 = sparse([1 1 1]);
assert_checkequal(getJc(sp1), int32([1 2 3]));
assert_checkequal(getJc(sp2), int32([1 2 3]));
