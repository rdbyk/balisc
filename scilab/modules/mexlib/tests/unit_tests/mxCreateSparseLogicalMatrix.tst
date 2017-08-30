// ============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2017-2017 - Gsoc 2017 - Siddhartha Gairola
//
//  This file is distributed under the same license as the Scilab package.
// ============================================================================

// <-- CLI SHELL MODE -->
// ============================================================================
// Unitary tests for mxCreateSparseLogicalMatrix mex function
// ============================================================================

cd(TMPDIR);
ilib_verbose(0);
mputl(["#include ""mex.h""";
"void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])";
"{";
"    mxArray *pOut1 = mxCreateSparseLogicalMatrix(2, 2, 0);";
"    mxArray *pOut2 = mxCreateSparseLogicalMatrix(3, 4, 0);";
"    plhs[0] = pOut1;";
"    plhs[1] = pOut2;";
"}"],"mexCreateSparseLogicalMatrix.c");
ilib_mex_build("libmextest",["createSparseLogical","mexCreateSparseLogicalMatrix","cmex"], "mexCreateSparseLogicalMatrix.c",[]);
exec("loader.sce");

[out1, out2] = createSparseLogical();

assert_checkequal(size(out1), [2, 2]);
assert_checkequal(size(out2), [3, 4]);
