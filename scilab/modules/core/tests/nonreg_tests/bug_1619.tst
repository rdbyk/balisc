// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2006-2008 - INRIA - Serge STEER <serge.steer@inria.fr>
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- NO CHECK REF -->

// <-- Non-regression test for bug 1619 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=1619
//
// <-- Short Description -->
//    macr2tree doesn't like functions compiled for profiling. It hates them
//    so much,
//    that causes spectacular crashes of scilab.

deff("x=foo(n)",["if n==0 then"
"  x=[]"
"else"
"  x=0"
"  for k=1:n"
"    s=svd(rand(n+10,n+10))"
"    x=x+s(1)"
"  end"
"end"])
assert_checkequal(execstr("macr2tree(foo)","errcatch"), 0);
clear foo;

function y=foo(),y=sin(33)+1;endfunction
foo(); //execution creates a deleted op in the pseudo code of foo
assert_checkequal(execstr("macr2tree(foo)","errcatch"), 0);
