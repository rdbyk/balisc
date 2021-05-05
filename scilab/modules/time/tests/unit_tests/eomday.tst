// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2007-2008 - INRIA - Pierre MARECHAL <pierre.marechal@inria.fr>
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// Error messages
assert_checkerror("eomday()", [], 71);
assert_checkerror("eomday(""toto"", 1)", [], 111);
assert_checkerror("eomday(12.5, 1)", [], 111);
assert_checkerror("eomday(%i, 1)", [], 111);
assert_checkerror("eomday(2000, ""toto"")", [], 111);
assert_checkerror("eomday(2000, 5.5)", [], 111);
assert_checkerror("eomday(2000, %i)", [], 111);
errmsg = msprintf(gettext("%s: Wrong size for input arguments #%d and #%d: Same sizes expected.\n"),"eomday", 1, 2);
assert_checkerror("eomday(1, [1 2])", errmsg);
assert_checkerror("eomday(2000, 0)", [], 110);
assert_checkerror("eomday(2000, 13)", [], 110);

years    = 1900:1999;

[nr,nc]  = size(years);
months   = 2 * ones(nr,nc);

E        = eomday(years,months);
test     = years(find(E == 29));
test_ref = [ 1904 1908 1912 1916 1920 1924 1928 1932 1936 1940 1944 1948 1952 1956 1960 1964 1968 1972 1976 1980 1984 1988 1992 1996 ];

assert_checkequal(test, test_ref);
