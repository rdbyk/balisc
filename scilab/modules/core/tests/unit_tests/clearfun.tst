// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

//================================================
// test clearfun , funptr, newfun
//================================================
if clearfun('myfunctionname') <> %F then pause,end
//================================================
newfun("MY_PWD","pwd");

assert_checktrue(clearfun("MY_PWD"));
//================================================
errmsg =  msprintf(gettext("%s: Wrong type for input argument #%d: String expected.\n"), "clearfun", 1);
assert_checkerror('a = clearfun(2);', errmsg);
