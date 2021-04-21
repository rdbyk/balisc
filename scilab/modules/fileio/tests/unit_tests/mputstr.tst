// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

this_file = pathconvert(TMPDIR+"/mputstr.txt",%F);

fd = mopen(this_file,"wt");
mputstr("Scilab",fd);
mclose(fd);

if mgetl(this_file) <> "Scilab" then pause,end

assert_checkerror('mputstr(""Scilab"",5)', [], 50);
