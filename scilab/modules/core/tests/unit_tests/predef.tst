// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA
// Copyright (C) 2009 - DIGITEO - Allan CORNET
// Copyright (C) 2015 - Scilab Enterprises - Antoine ELIAS
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
//

a = 1;
protect();

ierr = execstr("clear a","errcatch");
assert_checktrue(ierr <> 0);

ierr = execstr("unprotect()","errcatch");
assert_checktrue(ierr == 0);

ierr = execstr("clear a","errcatch");
assert_checktrue(ierr == 0);

assert_checktrue(length(isprotected()) == 0);
