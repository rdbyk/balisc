// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2010 - DIGITEO - Allan CORNET
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- Non-regression test for bug 7946 -->
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// 
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=7946
//
// <-- Short Description -->
// error(0, "bye") crashed Scilab

if execstr("error(0, ""bye"");", "errcatch") <> 999 then pause, end
if lasterror() <> msprintf(_("%s: Wrong value for input argument #%d: Value greater than 0 expected.\n"), "error", 1) then pause, end

if execstr("error(-10, ""bye"");", "errcatch") <> 999 then pause, end
if lasterror() <> msprintf(_("%s: Wrong value for input argument #%d: Value greater than 0 expected.\n"), "error", 1) then pause, end

if execstr("error(2000, ""Hello"");", "errcatch") <> 2000 then pause, end
if lasterror() <> "Hello" then pause, end
