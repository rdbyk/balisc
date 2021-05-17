// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - SCILAB ENTERPRISES - Simon GARESTE
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

assert_checkerror("h5label()", [], 77);
assert_checkerror("h5label(42)", [], 77);
assert_checkerror("h5label(42,42,42,42)", [], 90);
assert_checkerror("h5label(""42"",42,42,42)", [] ,91);
assert_checkerror("h5label(""42"",""42"",42,42)", [], 90);
assert_checkerror("h5label(""42"",""42"",42,[""42""])", [], 132);

a = h5open(TMPDIR + "/test.h5", "w");
assert_checkerror("h5label(a,""42"",42,[""42""])", [], 132);

x = uint8(1:24);
h5dataset(a, "Dset_1", [1 2 3 4 ; 1 1 1 1 ; 1 1 1 1 ; 1 1 1 1; 1 2 3 4], x, [1 2 3 4 ; 1 2 3 4 ; 1 1 1 1 ; 1 1 1 1 ; 1 1 1 1 ; 1 2 3 4]);
h5label(a, "Dset_1", [1 3], ["Hello" "World"]);
assert_checkequal(a.root.Dset_1.DIMENSION_LABELS.data,["Hello" "" "World" ""]);
h5close(a)
