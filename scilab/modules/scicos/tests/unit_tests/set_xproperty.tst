// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Paul Bignier
// Copyright (C) ????-2008 - INRIA
// Copyright (C) 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

refMsg = msprintf(_("%s: scicosim is not running.\n"), "set_xproperty");
assert_checkerror("set_xproperty(-1)", refMsg);
assert_checkerror("set_xproperty(1)", refMsg);
