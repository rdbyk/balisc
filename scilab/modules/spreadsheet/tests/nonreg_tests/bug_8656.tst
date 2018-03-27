//<-- CLI SHELL MODE -->
// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - S/E - Sylvestre Ledru
// Copyright (C) 2018 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// 
// <-- JAVA NOT MANDATORY -->
//
// <-- Non-regression test for bug 8656 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=8656
//
// <-- Short Description -->
// Lost of precision
//
A = [1.01234567891234567,1.01234567891234567];
filename=fullfile(TMPDIR,'data.csv');
csvWrite(A,filename,",",".");
resString=mgetl(filename);
assert_checkequal(A,evstr(resString));

res=csvRead(filename);
assert_checkequal(A,res);
