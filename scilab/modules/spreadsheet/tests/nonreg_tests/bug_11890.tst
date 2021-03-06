//<-- CLI SHELL MODE -->
// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - Scilab Enterprises - Sylvestre Ledru
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// 
// <-- JAVA NOT MANDATORY -->
//
// <-- Non-regression test for bug 11890 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=11890
//
// <-- Short Description -->
// Wrong parsing with empty char at the end of the line
//
content_ref = [ "1;2;3" ..
"4;5;"];
filename=TMPDIR+"/foo.csv";

mputl(content_ref,filename);

content_2=csvRead(filename,";");
assert_checkequal(content_2,[1,2,3;4,5,%nan]);
content_2(2,3)=42;
assert_checkequal(content_2,[1,2,3;4,5,42]);
