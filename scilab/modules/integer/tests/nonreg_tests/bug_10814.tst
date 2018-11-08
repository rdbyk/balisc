// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Allan CORNET
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// ===========================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 10814 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=10814
//
// <-- Short Description -->
// non regression test about overload and iconvert
//
M = mlist(['V', 'name', 'value'], ['a', 'b';'c' 'd'], [1 2; 3 4]);

msgerr = [msprintf(gettext("Function not defined for given argument type(s),\n"));
          msprintf(gettext("check arguments or define function %s for overloading.\n"), "%V_" + "iconvert")];
assert_checkerror ("iconvert(M, 0)", msgerr);

function bOK = %V_iconvert(X, Y)
  bOK = %T;
endfunction

assert_checktrue(iconvert(M, 0));
