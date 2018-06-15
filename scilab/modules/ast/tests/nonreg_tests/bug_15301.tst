// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2017 - ESI - Delamarre Cedric
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for bug 15301 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/15301
//
// <-- Short Description -->
// Sequence constructor ':' failed when a bound was an outputless funtion call

errmsg = sprintf(_("%ls: Evaluation of argument %d yields no result.\n"), "'':''",2);
assert_checkerror("1:disp(""ok"")", errmsg);
