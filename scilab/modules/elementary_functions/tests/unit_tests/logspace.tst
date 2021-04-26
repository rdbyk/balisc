// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Michael Baudin
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// Basic use
computed=logspace(0,10,11);
expected=10 .^ (0:10);
assert_checkalmostequal(computed,expected);

assert_checkequal(logspace(1,2,-1),[]);
assert_checkequal(logspace(1,2,0),[]);

// Vector input
assert_checkequal(size(logspace([0;2],[2;5],5)),[2,5]);
assert_checkequal(size(logspace([0;2],[2;5],2)),[2,2]);
assert_checkequal(logspace([0;2],[2;4],3),[1,10 100;100 1000 10000]);
assert_checkequal(logspace([-1;2],[2;6],6), [logspace(-1,2,6);logspace(2,6,6)]);

// Perform a check on the size of the input arguments
assert_checktrue(execstr('logspace(2,[2,2])','errcatch') <> 0);
assert_checktrue(lasterror() <> []);
