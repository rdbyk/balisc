// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA
// Copyright (C) 2012 - DIGITEO - Vincent COUVERT
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- ENGLISH IMPOSED -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

refMsg = msprintf(_("%s: Wrong number of input arguments: %d to %d expected.\n"), "editvar", 1, 4);
assert_checkerror("editvar();", refMsg);

assert_checkerror("editvar(1,2,3);", [], 76);
assert_checkerror("editvar([]);", [], 91);
assert_checkerror("editvar(12);", [], 91);

clear __ghost
assert_checkerror("editvar(""__ghost"");",  [], 40);
