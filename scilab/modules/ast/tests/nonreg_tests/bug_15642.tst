// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2018 - Stéphane MOTTELET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
//
// <-- Non-regression test for bug 15642 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/15642
//
// <-- Short Description -->
// A(:) gives incorrect display when A is sparse boolean (regression)

A=sparse([1 1; 2 2; 3 3],[%t %f %t],[3 3]);
A(:)
