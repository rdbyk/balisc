// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for bug 10444 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=10444
//
// <-- Short Description -->
// Bug #10444 fixed - fullfile did not manage string matrix as last input argument.
//

assert_checkerror ("r = fullfile(SCI, 3, ''scilab.start'')", [], 91);

if getos() <> "Windows" then
  REF = ['/home/scilab/macros/util/fullfile.sci';
         '/home/scilab/macros/util/toto.sci'];
else
  REF = ['\home\scilab\macros\util\fullfile.sci';
         '\home\scilab\macros\util\toto.sci'];
end

r = fullfile("/home/","\scilab","macros","\util", ["fullfile.sci"; "toto.sci"]);
assert_checkequal(r, REF);
