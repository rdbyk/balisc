// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 3907 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=3907
//
// <-- Short Description -->
// msprintf invalid format can kill scilab

assert_checkerror("msprintf(''%s%d%s%s'',''r'',''e'',''w'',1);", [], 150);

msprintf('%s%d%s%s','r',1,'e','w')
