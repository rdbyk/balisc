// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2007-2008 - INRIA
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

assert_checkerror("strcat()", [], 71);
assert_checkerror("strcat(%f)", [], 91);
assert_checkerror("strcat(""test"", """", ""f"")", [], 110);
assert_checkerror("strcat([],3)", [], 90);
assert_checkerror("strcat(1,""x"",1)", [], 90);

assert_checkequal(strcat(["abc" "abd","aa" "bxe"]), "abcabdaabxe");
assert_checkequal(strcat(["abc";"abd";"aa";"bxe"]), "abcabdaabxe");
assert_checkequal(strcat(["abc" "abd";"aa" "bxe"]), "abcaaabdbxe");

assert_checkequal(strcat(["abc","abd","aa","bxe"],","), "abc,abd,aa,bxe");
assert_checkequal(strcat("abc"), "abc");

assert_checkequal(strcat("abc","sd"), "abc");
assert_checkequal(strcat(""), "");
assert_checkequal(strcat(["" ""]), "");
assert_checkequal(strcat(["";""]), "");

assert_checkequal(strcat([]), []);
assert_checkequal(strcat([], ""), []);
assert_checkequal(strcat([], "3"), []);

assert_checkequal(strcat(["abc","abd","aa","bxe"],"--"), "abc--abd--aa--bxe");

assert_checkequal(strcat(["abc" "abd";"aa" "bxe"], '-', 'r'), ["abc-aa" "abd-bxe"]);
assert_checkequal(strcat(["abc" "abd";"aa" "bxe"], '-', 'c'), ["abc-abd";"aa-bxe"]);

assert_checkequal(strcat(["" "A" "" "B" ""], ","), [",A,,B,"]);
assert_checkequal(strcat(["";"A";"";"B";""], ","), [",A,,B,"]);

assert_checkequal(strcat(["" "A" "";"B" "" "C"], ",", "r"), [",B" "A," ",C"]);
assert_checkequal(strcat(["" "A" "";"B" "" "C"], ",", "c"), [",A,";"B,,C"]);
