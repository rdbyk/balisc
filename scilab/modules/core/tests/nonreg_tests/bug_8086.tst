// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Allan CORNET
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 8086 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=8086
//
// <-- Short Description -->
// Wrong error message was displayed when no input argument provided
//

macros_error_type_1 = ["isscalar"; ..
"acosd"; ..
"acot"; ..
"acotd"; ..
"acoth"; ..
"acsc"; ..
"acscd"; ..
"acsch"; ..
"asec"; ..
"asecd"; ..
"asech"; ..
"asind"; ..
"atand"; ..
"bin2dec"; ..
"cat"; ..
"convertindex"; ..
"cosd"; ..
"cotd"; ..
"csc"; ..
"cscd"; ..
"csch"; ..
"csgn"; ..
"factor"; ..
"int"; ..
"hex2dec"; ..
"isempty"; ..
"isinf"; ..
"isnan"; ..
"isvector"; ..
"log10"; ..
"log2"; ..
"logm"; ..
"ndims"; ..
"nextpow2"; ..
"oct2dec"; ..
"pertrans"; ..
"primes"; ..
"sec"; ..
"secd"; ..
"sech"; ..
"signm"; ..
"sinc"; ..
"sind"; ..
"sqrtm"; ..
"squarewave"; ..
"sub2ind"; ..
"tand" ..
];
msg_error_ref_1 = _("%s: Wrong number of input arguments: %d expected.\n");
for i=1:size(macros_error_type_1, "*")
    assert_checkerror (macros_error_type_1(i) + "()" , msg_error_ref_1 , [] , macros_error_type_1(i) , 1);
end

macros_error_type_2 = ["binomial"; ..
"bitand"; ..
"ind2sub"; ..
"modulo"; ..
"permute"; ..
"pmodulo"; ..
"union" ..
];
msg_error_ref_2 = _("%s: Wrong number of input arguments: %d expected.\n");
for i=1:size(macros_error_type_2, "*")
    assert_checkerror (macros_error_type_2(i) + "()" , msg_error_ref_2 , [] , macros_error_type_2(i) , 2);
end

macros_error_type_3 = ["complex"];
msg_error_ref_3 = _("%s: Wrong number of input arguments: %d to %d expected.\n");
for i=1:size(macros_error_type_3, "*")
    assert_checkerror (macros_error_type_3(i) + "()" , msg_error_ref_3 , [] , macros_error_type_3(i) , 1, 2);
end

macros_error_type_4 = ["system"];
msg_error_ref_4 = _("%s: Wrong number of input argument(s).\n");
for i=1:size(macros_error_type_4, "*")
    assert_checkerror (macros_error_type_4(i) + "()" , msg_error_ref_4 , [] , macros_error_type_4(i));
end

macros_error_type_6 = ["max", "min"];
msg_error_ref_6 = _("%s: Wrong number of input arguments: at least %d expected.\n");
for i=1:size(macros_error_type_6, "*")
    assert_checkerror (macros_error_type_6(i) + "()" , msg_error_ref_6 , [] , macros_error_type_6(i), 1);
end

macros_error_type_5 = ["flipdim"; "linspace"; "base2dec"];
msg_error_ref_5 = _("%s: Wrong number of input arguments: %d to %d expected.\n");
for i=1:size(macros_error_type_5, "*")
    assert_checkerror (macros_error_type_5(i) + "()" , msg_error_ref_5 , [] , macros_error_type_5(i) , 2, 3);
end
