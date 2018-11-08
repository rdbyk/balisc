// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Vincent COUVERT
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// Check that javahelp files are present and non-zero size for current language

helpFile = "SCI/modules/helptools/jar/scilab_" + getlanguage() + "_help.jar";
assert_checktrue(isfile(helpFile));
[x, ierr] = fileinfo(helpFile);
assert_checktrue(ierr==0);
assert_checktrue(x(1) > 0);
