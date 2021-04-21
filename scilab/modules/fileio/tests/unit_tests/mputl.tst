// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2007-2008 - INRIA - Bruno JOFRET <bruno.jofret@inria.fr>
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

assert_checkerror('mputl()', [], 71);
assert_checkerror('mputl(1)', [], 71);

// TEST 1 : dummy file
cd TMPDIR;
// Deleting an existing file... Just in case...
mdelete("dummyFile.dummy")

TXT = [ 'I am a dummy String'; ..
        'Multi lines '; ..
        'to check that'; ..
        ' mputl is okay'; ..
        ' on linux and windows ... '];

r = mputl(TXT, 'dummyFile.dummy');
if r <> %T then pause,end
TXT2 = mgetl('dummyFile.dummy');

if TXT2 <> TXT then pause,end
// =============================================================================
// Testing if the file created exists
lsResult = ls("dummyFile.dummy");
if lsResult == []      then pause,end

// Now delete it
mdelete("dummyFile.dummy")
// =============================================================================

assert_checkerror('mputl(TXT, 5)', [], 50);
