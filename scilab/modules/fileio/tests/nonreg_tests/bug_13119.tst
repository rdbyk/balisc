// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Paul Bignier
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for bug 13119 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=13119
//
// <-- Short Description -->
// mget and mgetl accepted decimal values as number of lines.

curdir = pwd();
cd(TMPDIR);

fd = mopen("test", "w"); // Open a file

assert_checkerror("mget(-1, ""d"", fd)", [], 110);
assert_checkerror("mget(1.5, ""d"", fd)", [], 110);
assert_checkerror("mget(int8(1), ""d"", fd)", [], 93);
assert_checkerror("mgetl(""test"", 1.5)", [], 111);
assert_checkerror("mgetl(""test"", int8(1))", [], 93);

mclose(fd);
deletefile("test");

cd(curdir);
