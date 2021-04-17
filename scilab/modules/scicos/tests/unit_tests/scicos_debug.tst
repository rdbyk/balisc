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

assert_checkequal(scicos_debug_count(), 0);

level = 0;
assert_checkequal(scicos_debug(), level);

level = 2;
scicos_debug(level);
assert_checkequal(scicos_debug(), level);
