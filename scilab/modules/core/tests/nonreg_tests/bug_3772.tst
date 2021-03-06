//<-- CLI SHELL MODE -->
// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - DIGITEO - Allan CORNET
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- Non-regression test for bug 3772 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=3772
//
// <-- Short Description -->
// input argument in predef function not correctly checked

ierr = execstr('protect([1 2])','errcatch');
if ierr <> 999 then pause,end

ierr = execstr('protect(''non_existent'')','errcatch');
if ierr <> 999 then pause,end
