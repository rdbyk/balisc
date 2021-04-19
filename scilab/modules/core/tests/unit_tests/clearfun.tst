
// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

if clearfun('myfunctionname') <> %F then pause,end

newfun("MY_PWD","pwd");
assert_checktrue(clearfun("MY_PWD"));

assert_checkerror('a = clearfun(2);', [], 91);
