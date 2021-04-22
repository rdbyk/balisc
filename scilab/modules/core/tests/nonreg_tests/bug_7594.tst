// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2010 - INRIA - Serge STEER <serge.steer@inria.fr>
// Copyright (C) 2014 - Scilab Enterprises - Anais AUBERT
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 7594 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=7594
//
// <-- Short Description -->
// Incorrect  error detection since bug 6781 fix

function foo1()
    a=xxxxxxx
endfunction

function foo2()
    a=1:xxxxxxx
endfunction

clear xxxxxxx ;//to make sure xxxxxxx does not exist

assert_checkerror("foo()", [], 40);
assert_checkerror("foo2()", [], 40);
