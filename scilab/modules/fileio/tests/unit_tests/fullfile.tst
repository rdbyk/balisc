// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

assert_checkequal(fullfile([]), []);
assert_checkequal(fullfile([],[]), []);
assert_checkequal(fullfile([],[],[]), []);

assert_checkerror ("fullfile()" , [], 74);

REF = SCI + '/etc/scilab.start';
r = fullfile(SCI, '/etc/', 'scilab.start');

if getos() <> "Windows" then
  REF1 =  "/home/scilab/macros/util/fullfile.sci";
  REF2 =  "/cygdrive/C/scilab/macros/util/fullfile.sci";
else
  REF1 =  "\home\scilab\macros\util\fullfile.sci";
  REF2 =  "C:\scilab\macros\util\fullfile.sci";
end

r1 = fullfile("/home/", "\scilab", "macros", "\util", "fullfile.sci");
r2 = fullfile("C:", "\scilab", "macros", "\util", "fullfile.sci");
assert_checkequal(r1, REF1);
assert_checkequal(r2, REF2);

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
