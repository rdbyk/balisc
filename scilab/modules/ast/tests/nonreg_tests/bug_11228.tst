// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2018 - Samuel GOUGEON
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// <-- CLI SHELL MODE -->
// <-- ENGLISH IMPOSED -->
//
// <-- Non-regression test for bug 11228 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/11228
//
// <-- Short Description -->
// Some recursive extraction from a mlist was not done in the right
// order and yielded a stack problem

a = mlist('A');
deff('y=%A_e(name,a)','disp(name);if name~=''e'' then y=mlist(''A''), else y=clc, end')

a.b.c.d.e()
