// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Allan CORNET
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for bug 10306 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=10306
//
// <-- Short Description -->
// 'isempty' could fail with empty elements in a list
//

voidelement = list([],[],[]);
assert_checktrue(isempty(voidelement));

voidelement = list('','','');
assert_checktrue(isempty(voidelement));

voidelement = list(2,1,3);
assert_checkfalse(isempty(voidelement));
