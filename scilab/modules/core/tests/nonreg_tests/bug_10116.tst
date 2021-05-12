// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Samuel GOUGEON
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- TEST WITH GRAPHIC -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->
//
// <-- Non-regression test for bug 10116 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/10116
//
// <-- Short Description -->
// for h = vector_of_handles, .., end  was not supported

plot()
f = gcf();

for c = f.children
end
