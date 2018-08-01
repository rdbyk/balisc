// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Samuel GOUGEON
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 7649 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/7649
//
// <-- Short Description -->
//  isempty() returned %F  on {}, list(,) struct() or struct without field
// =============================================================================

assert_checktrue(isempty({}));
assert_checktrue(isempty(struct()));
assert_checktrue(isempty(list()));
assert_checktrue(isempty(list([],struct(),{},list())));
assert_checktrue(isempty({[],struct(),{}, list([])}));
s(1).w = list();
s(2).w = struct();
s(3).w = {};
s(4).w = [];
assert_checktrue(isempty(s));
s.w = null();
assert_checktrue(isempty(s));
