// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2005-2008 - INRIA - Serge Steer
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- Non-regression test for bug 1384 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=1384
//
// <-- Short Description -->
// Missing test and error for resume called with indexed output arguments
clear foo;deff('foo()','a(2)=return(1)');
if execstr('foo()','errcatch')<>79 then pause,end

clear foo;deff('foo()','a=return(1)');
if execstr('foo()','errcatch')<>0 then pause,end


clear foo;deff('foo()','[a(3),b]=return(1,2)');
if execstr('foo()','errcatch')  <>79 then pause,end

clear foo;deff('foo()','[a,b]=return(1,2)');
if execstr('foo()','errcatch')<>0 then pause,end


clear foo;deff('foo()','a(2)=return(1)');
if execstr('foo()','errcatch')<>79 then pause,end

clear foo;deff('foo()','a=return(1)');
if execstr('foo()','errcatch')<>0 then pause,end

clear foo;deff('foo()','[a(3),b]=return(1,2)');
if execstr('foo()','errcatch')<>79 then pause,end


clear foo;deff('foo()','[a,b]=return(1,2)');
if execstr('foo()','errcatch')<>0 then pause,end


