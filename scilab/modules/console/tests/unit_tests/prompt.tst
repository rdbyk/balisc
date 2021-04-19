// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
// Copyright (C) 2017 - ESI Group - Paul Bignier
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// =============================================================================

curprompt = prompt();
assert_checkequal(curprompt, ascii([45 45 62 32]));

[curprompt, pause_level] = prompt();
assert_checkequal(curprompt, ascii([45 45 62 32]));
assert_checkequal(pause_level, 0);

prompt("-- My Prompt -->");
1+1;

ierr = execstr("[a, b, c] = prompt();", "errcatch");
assert_checkequal(ierr, 82);

ierr = execstr("[a, b] = prompt(1);", "errcatch");
assert_checkequal(ierr, 81);

ierr = execstr("[a, b] = prompt(""1"");", "errcatch");
assert_checkequal(ierr, 81);

ierr = execstr("prompt(""1234567890123456789012345678901234567890123456789012345678901234"");", "errcatch");
assert_checkequal(ierr, 0);

ierr = execstr("prompt(""123456789012345678901234567890123456789012345678901234567890123"");", "errcatch");
assert_checkequal(ierr, 0);

ierr = execstr("prompt(""这段文字很长这段文字很长这段文字很长这段文字很长这段文字很长"");", "errcatch");
assert_checkequal(ierr, 0);
