// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Scilab Enterprises -
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

//<-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 14177 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/14177
//
// <-- Short Description -->
// Using Java interface functions crashes Scilab in NWNI mode
//

assert_checkerror("jcompile()", [], 26);
