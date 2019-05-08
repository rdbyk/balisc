// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014-2014 - Scilab Enterprises - Bruno JOFRET
// Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

a=list(list(1));
b=a;
b(1)(1) = 2;
// a must not be modified !
assert_checkequal(a, list(list(1)));
