// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

A = 2;
B = 4;
C = 6;
clear("B")
assert_checkequal(isdef("B"), %f);
assert_checkequal(isdef("A"), %t);
assert_checkequal(isdef("C"), %t);

clear();
assert_checkequal(isdef("A"), %f);
assert_checkequal(isdef("C"), %f);

A = 2;
B = 4;
C = 6;
D = 8;
clear( ["A" "B" "C" "D"] );
assert_checkequal(isdef("A"), %f);
assert_checkequal(isdef("B"), %f);
assert_checkequal(isdef("C"), %f);
assert_checkequal(isdef("D"), %f);

A = 2;
B = 4;
C = 6;
D = 8;
clear( ["A" ; "B" ; "C" ; "D"] );
assert_checkequal(isdef("A"), %f);
assert_checkequal(isdef("B"), %f);
assert_checkequal(isdef("C"), %f);
assert_checkequal(isdef("D"), %f);

A = 2;
B = 4;
C = 6;
D = 8;
clear( ["A" "B" ; "C" "D"] );
assert_checkequal(isdef("A"), %f);
assert_checkequal(isdef("B"), %f);
assert_checkequal(isdef("C"), %f);
assert_checkequal(isdef("D"), %f);

A = 2;
B = 4;
C = 6;
D = 8;
clear( ["A" "B"], ["C";"D"] );
assert_checkequal(isdef("A"), %f);
assert_checkequal(isdef("B"), %f);
assert_checkequal(isdef("C"), %f);
assert_checkequal(isdef("D"), %f);


function test_clear()
    A = 6;
    clear("A")
    assert_checkequal(isdef("A"), %f);
endfunction
test_clear();
A = 3;
assert_checkequal(isdef("A"), %t);
assert_checkequal(A, 3);

ierr = execstr("clear SCI", "errcatch");
assert_checkequal (ierr, 4);

assert_checktrue(isdef("SCI"));
oldSCI = SCI;
ierr = execstr("SCI = 14;", "errcatch");
assert_checkequal (ierr, 4);

assert_checktrue(isdef("SCI"));
assert_checkequal(oldSCI, SCI);

ierr = execstr("clear(1)", "errcatch");
assert_checkequal (ierr, 90);

ierr = execstr("clear toto", "errcatch");
assert_checkequal(ierr, 0);
