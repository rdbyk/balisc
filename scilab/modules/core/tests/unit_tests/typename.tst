// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

[typs,nams]=typename();
if or(typs<>[1;2;4;5;6;7;8;9;10;11;13;14;15;16;17;128;129;130]) then pause,end
if or(nams<>["s";"p";"b";"sp";"spb";"msp";"i";"h";"c";"m";"mc";"f";"l";"tl";"ml";"ptr";"ip";"fptr"])  then pause,end

assert_checkerror("typename(''hgh'')", [], 71);
assert_checkerror("typename([17])", [], 71);
assert_checkerror("typename(''my type'',110)", [], 71);
