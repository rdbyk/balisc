// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - DIGITEO
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

assert_checkerror("system_setproperty();", [], 71);
assert_checkerror("system_getproperty();", [], 71);
assert_checkerror("a = system_setproperty(""TOTO"",2);", [], 91);

r = system_getproperty("TOTO");
assert_checkequal(r, "unknown");

a = system_setproperty("TOTO","TATA");
assert_checkequal(a, []);
r = system_getproperty("TOTO");
assert_checkequal(r, "TATA");

a = system_setproperty("TOTO","TITI");
assert_checkequal(a, "TATA");
r = system_getproperty("TOTO");
assert_checkequal(r, "TITI");
