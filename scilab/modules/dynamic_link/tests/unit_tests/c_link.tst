// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA
// Copyright (C) 2009 - DIGITEO
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

assert_checkerror('c = c_link()', [], 72);

c = c_link('a_name_lib');
if c <> %F then pause,end

[a,b] = c_link('a_name_lib');
if a <> %F then pause,end
if b <> -1 then pause,end

c = c_link('a_name_lib',-1);
if c <> %F then pause,end

[a,b] = c_link('a_name_lib',-1);
if a <> %F then pause,end
if b <> -1 then pause,end
