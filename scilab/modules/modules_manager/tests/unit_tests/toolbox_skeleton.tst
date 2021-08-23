// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Vincent COUVERT
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->
// <-- ENGLISH IMPOSED -->

// Test the toolbox skeleton in SCI/contrib/
//  - Building/Compilation
//  - Loading
//  - Tests

// Scilab external module skeleton
status = copyfile(SCI + "/contrib/toolbox_skeleton/", TMPDIR + "/toolbox_skeleton/");
assert_checkequal(status, 1);
exec("TMPDIR/toolbox_skeleton/builder.sce");
exec("TMPDIR/toolbox_skeleton/loader.sce");
test_run("TMPDIR/toolbox_skeleton/", [], ["short_summary" "no_check_error_output"]);
