//<-- CLI SHELL MODE -->
// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- NO TRY CATCH -->

//error
execstr("error(""test erreur"")", "errcatch");
errclear();
assert_checkequal(lasterror(), []);

execstr("error(""test erreur"", 999)", "errcatch");
errclear();
[m,n]=lasterror();
assert_checkequal(m, []);
assert_checkequal(n, 0);

// lasterror
execstr("unknown", "errcatch");
assert_checkequal(stripblanks(lasterror(%f)), "Undefined variable: ''unknown''.");
[m,n]=lasterror();
assert_checkequal(stripblanks(m), "Undefined variable: ''unknown''.");
assert_checktrue(n <> 0);
assert_checkequal(lasterror(), []);
[m,n]=lasterror();
assert_checkequal(m, []);
assert_checkequal(n, 0);
