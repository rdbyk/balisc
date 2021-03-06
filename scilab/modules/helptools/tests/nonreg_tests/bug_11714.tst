// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Paul Bignier
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- NO CHECK REF -->
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for bug 11714 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=11714
//
// <-- Short Description -->
// help_from_sci sometimes failed when function had "<imagedata>" comments.

path = SCI+"/modules/helptools/tests/nonreg_tests/";
copyfile(path+"bug_11714.sci", TMPDIR + filesep());
path = TMPDIR + filesep();

help_from_sci(path+"bug_11714.sci", path); // Create bug_11714.xml

assert_checktrue(isfile(path+"bug_11714.xml"));
fd = mopen(path+"bug_11714.xml");
mgetl(fd, 28);
image = mgetl(fd, 1); // Read the 29th line of bug_11714.xml

refImage = "<imagedata fileref=""myimage.png"" align=""center"" valign=""middle""/>";
assert_checkequal(image, refImage);

mclose(fd);
deletefile(path+"bug_11714.xml");
