// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Charlotte HECQUET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- ENGLISH IMPOSED -->
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 12551 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=12551
//
// <-- Short Description -->
// Stack problem with diary([],"pause") and diary([],"resume")
//

FILENAME_DIARY = TMPDIR +'/foo.log';
fd = diary(FILENAME_DIARY, 'new');
FILENAME_DIARY2 = TMPDIR +'/foo2.log';
fd2 = diary(FILENAME_DIARY2, 'new');
a=1;

diary([],"pause");
a=2;
txt = mgetl(FILENAME_DIARY); 
txt($)
assert_checkequal(txt($), prompt() + "diary([],""pause"");");
txt2 = mgetl(FILENAME_DIARY2);
assert_checkequal(txt2($), prompt() + "diary([],""pause"");");

diary([],"resume");
a=3;
diary([],"close");
txt=mgetl(FILENAME_DIARY);
assert_checkequal(txt($-2), prompt() + "a=3;");
txt2=mgetl(FILENAME_DIARY2);
assert_checkequal(txt($-2), prompt() + "a=3;");
