// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Vincent COUVERT
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 11227 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=11227
//
// <-- Short Description -->
// Scilab crashed when trying to use a structure with a non-existing field name containing "%"

// Existing field name
a = struct();
a("toto%")=2;
assert_checkequal(a("toto%"), 2);

clear a

// Non-existing field name
refMsg = gettext("Unknown field: toto.");
a = struct();
assert_checkerror("a(""toto"")", refMsg);
