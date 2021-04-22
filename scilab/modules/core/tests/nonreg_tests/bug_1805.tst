// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2005-2008 - INRIA - Serge Steer
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 1805 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/1805
//
// <-- Short Description -->

funcprot(0);

function varargout=test(),varargout="";a=1,endfunction
assert_checkerror("test()", [], 43)

function varargout=test();a=1,endfunction
assert_checkerror("x=test()", [], 81)
