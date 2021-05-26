// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Vincent COUVERT <vincent.couvert@scilab.org>
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- ENGLISH IMPOSED -->

// <-- Non-regression test for bug 4926 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=4926
//
// <-- Short Description -->
// Can not save a structure in a MAT-file using savematfile.

s.name = "NAME";
s.firstname = "FIRSTNAME";
s.age = 25;
s.address = "TOWN";

savematfile(TMPDIR + filesep() + "bug_4926.tst", "-v7", "s");
