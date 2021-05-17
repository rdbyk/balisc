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

assert_checkerror("h5dataset()", [], 77);
assert_checkerror("h5dataset(42)", [], 77);
assert_checkerror("h5dataset(42,42,42,42,42)", [], 90);
assert_checkerror("h5dataset(""42"",42,42,42,42)", [], 91);
assert_checkerror("h5dataset(""42"",""42"",[""42"",""42"",""42"",""42"",""42""],42,42)", [], 94);
assert_checkerror("h5dataset(""42"",""42"",[42;42;42;42;42],42,42)", [], 100);
assert_checkerror("h5dataset(""42"",""42"",[42;42;42;42;42],42,[42;42;42;42;42;42])", [], 132);

a = h5open(TMPDIR + "/test.h5", "w");

assert_checkerror("h5dataset(a,""42"",[42;42;42;42;42],42,[42;42;42;42;42;42])", [], 132);

x = uint32(1:100);
y = uint32(matrix(1:100,10,10));

z = uint32(zeros(7,12));
h5write(a,"dx",y',[2 1 ],[ 4 1 ],[ 2 1 ],[ 1 9 ]);
z(3:6,3:11) = a.root.dx.Data;

assert_checkerror("h5dataset(a, """", [10 10 ; 2 1 ; 4 1 ; 2 1 ; 1 9], x, [7 12 ; 9 14 ; 3 3 ; 1 1 ; 1 1 ; 4 9])", [], 132);
h5dataset(a, "D_set1", [10 10 ; 2 1 ; 4 1 ; 2 1 ; 1 9], x, [7 12 ; 9 14 ; 3 3 ; 1 1 ; 1 1 ; 4 9]);
assert_checkequal(a.root.D_set1.Data,z');

z = uint32(zeros(9,12));
z(1:5,1) = uint32([1;21;41;61;81]);
h5dataset(a, "D_set2", [5 20 ; 1 1 ; 1 1 ; 1 1 ; 5 1], y, [9 12 ; 9 14 ; 1 1 ; 1 1 ; 1 1 ; 5 1]);
assert_checkequal(a.root.D_set2.Data,z');

assert_checkerror("h5dataset(a, ""Dset_3"", [10 10 ; 2 1 ; 4 1 ; 2 1 ; 1 9], x, [10 10 ; 11 14 ; 3 3 ; 1 1 ; 1 1 ; 1 1])", [], 132);
assert_checkerror("h5dataset(a, ""D_set4"", [10 10 ; 2 1 ; 4 1 ; 2 1 ; 1 9], x, [7 12 ; 6 11 ; 3 3 ; 1 1 ; 1 1 ; 4 9])", [], 132);
