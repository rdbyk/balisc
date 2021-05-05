// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Sylvestre LEDRU
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

assert_checktrue(execstr("a = javalibrarypath(2);","errcatch")==999);

result = javalibrarypath();
assert_checktrue(size(result,"*") > 1);

// Does not return anything
assert_checktrue(execstr("javalibrarypath(TMPDIR);","errcatch")==0);
