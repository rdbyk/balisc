// ============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Sylvain GENIN
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// ============================================================================

// <-- TEST WITH GRAPHIC -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

//handle
handle1 = gcf();
handle2 = gca();

assert_checkequal(handle1 <> handle1, %f);
assert_checkequal(handle1 <> handle2, %t);

delete(handle1);
