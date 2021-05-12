// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2005-2008 - INRIA - Serge Steer
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 1384 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=1384
//
// <-- Short Description -->
// Missing test and error for resume called with indexed output arguments

funcprot(0);

errnum=28;

deff('foo()','a(2)=return(1)');
assert_checkerror('foo()', [], errnum);

deff('foo()','a=return(1)');
foo();

deff('foo()','[a(3),b]=return(1,2)');
assert_checkerror('foo()', [], errnum);

deff('foo()','[a,b]=return(1,2)');
foo();

deff('foo()','a(2)=return(1)');
assert_checkerror('foo()', [], errnum);

deff('foo()','a=return(1)');
foo();

deff('foo()','[a(3),b]=return(1,2)');
assert_checkerror('foo()', [], errnum);

deff('foo()','[a,b]=return(1,2)');
foo();
