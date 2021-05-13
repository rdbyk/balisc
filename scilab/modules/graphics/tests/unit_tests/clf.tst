// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2017 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH GRAPHIC -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

f = scf(100);
f.figure_name = "Test number 1 with clf";
f.figure_size = [300 200];
plot(1:10)
clf()
assert_checkequal(f.figure_id, 100);
assert_checkequal(f.figure_name, "Test number 1 with clf");
assert_checkequal(f.figure_size, [300 200]);
assert_checkequal(f.children.children, []);
plot(1:10)
clf("clear")
assert_checkequal(f.figure_id, 100);
assert_checkequal(f.figure_name, "Test number 1 with clf");
assert_checkequal(f.figure_size, [300 200]);
assert_checkequal(f.children.children, []);
clf("reset")
assert_checkequal(f.figure_id, 100);
assert_checkequal(f.figure_name, "Graphic window number %d");
assert_checkequal(f.figure_size, [620 590]);
assert_checkequal(f.children.children, []);
delete(f);

// clf must not reset figure_id
f0 = scf(0);
plot(1:10);
f1 = scf(1);
plot(1:20)
clf("reset")
assert_checkequal(f1.figure_id, 1);
delete(f0);
delete(f1);
