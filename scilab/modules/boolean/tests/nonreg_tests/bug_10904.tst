// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) DIGITEO - 2012 - Allan CORNET
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 10904 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/10904
//
// <-- Short Description -->
// error messages of and(), or() builtin were not standard.

a = 1;
b = 3;
c = 4;
d = 5;

// and

assert_checkerror("and(a == b, c == d)", [], 90);

msgerr = [msprintf(gettext("Function not defined for given argument type(s),\n"));
msprintf(gettext("check arguments or define function %s for overloading.\n"),"%c_and")];
assert_checkerror("and(""a"")", msgerr);

assert_checkerror("and(%T, [1 2])", [], 100);
assert_checkerror("and(%T, ''t'')", [], 110);
assert_checkerror("and(%T, %i)", [], 111);

// or

assert_checkerror("or(a == b, c == d)", [], 90);

msgerr = [msprintf(gettext("Function not defined for given argument type(s),\n"));
msprintf(gettext("check arguments or define function %s for overloading.\n"),"%c_or")];
assert_checkerror("or(""a"")", msgerr);

assert_checkerror("or(%T, [1 2])", [], 100);
assert_checkerror("or(%T, ''t'')", [], 110);
assert_checkerror("or(%T, %i)", [], 111);
