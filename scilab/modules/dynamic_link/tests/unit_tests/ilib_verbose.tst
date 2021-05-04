// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// test set/get ilib_verbose

ref = 1; // default value
r = ilib_verbose();
if r <> ref then pause,end

assert_checkerror('ilib_verbose([1 2]);', [], 111);
assert_checkerror('ilib_verbose(''foo'');', [], 111);
assert_checkerror('ilib_verbose(54);', [], 110);
assert_checkerror('ilib_verbose(5.4);', [], 111);

ref = 0;
ilib_verbose(ref)
r = ilib_verbose();
if r <> ref then pause,end

ref = 1;
ilib_verbose(ref)
r = ilib_verbose();
if r <> ref then pause,end

ref = 2;
ilib_verbose(ref)
r = ilib_verbose();
if r <> ref then pause,end
