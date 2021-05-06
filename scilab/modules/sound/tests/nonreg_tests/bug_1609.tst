// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 1609 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=1609
//
// <-- Short Description -->
// I can't freely choose "fs" parameter in the following example with 'sound'

// in a CI environment we redefine "sound" function as a nop dummy
funcprot(0);
if getenv("CI","FALSE") <> "FALSE" then
	function sound(y,z),end
end

y=loadwave("SCI/modules/sound/demos/chimes.wav");
sound(y,44100);
sound(y,22500);
