// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - Scilab Enterprises - Sylvestre Ledru
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

a=sparse([%t %t %t; %t %t %t]);
b=matrix(a,1,-1);
assert_checkequal(size(a), [2,3]);
assert_checkequal(size(b), [1,6]);
