// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2018 - Samuel GOUGEON
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- XCOS TEST -->
// <-- NO CHECK REF -->
// <-- ENGLISH IMPOSED -->
//
// <-- Non-regression test for bug 15757 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/15757
//
// <-- Short Description -->
// xcosPalAddBlock() did not load scicos_scicoslib when required.
// When providing the block as a missiong .sod file, the error message was misleading.

pal = xcosPal("Bug_15757");
h5 = pathconvert(SCI+"\modules\xcos\blocks\h5\blabla.sod",%f); // Does not exist
svg = pathconvert(SCI+"\modules\xcos\images\blocks\ConstantVoltage.svg",%f);
gif = pathconvert(SCI+"\modules\xcos\images\palettes\ConstantVoltage.png",%f);

cmd = "pal = xcosPalAddBlock(pal, h5, gif, svg)";
msg = "xcosPalAddBlock: Unable to load block from """ + h5 + """: Missing file.";
assert_checkerror(cmd, msg);

h5 = pathconvert(SCI+"\modules\xcos\tests\nonreg_tests\bug_15757.sod",%f);
assert_checkequal(execstr(cmd,"errcatch"),0);
