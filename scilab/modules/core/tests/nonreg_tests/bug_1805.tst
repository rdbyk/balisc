// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2005-2008 - INRIA - Serge Steer
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- ENGLISH IMPOSED -->

// <-- Non-regression test for bug 1805 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=1805
//
// <-- Short Description -->
//    avaragout oddities

funcprot(0);

function varargout=test(),varargout="";a=1,endfunction
assert_checkerror("test()", "test: Wrong type for ''varargout'': A list expected.")

function varargout=test();a=1,endfunction
assert_checkerror("x=test()", "test: Wrong number of output arguments: 0 expected.")
