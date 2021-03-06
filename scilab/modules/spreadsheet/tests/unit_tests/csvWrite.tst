// =============================================================================
// Copyright (C) 2011 - INRIA - Michael Baudin
// Copyright (C) 2010 - 2011 - INRIA - Allan CORNET
// Copyright (C) 2013 - Scilab Enterprises - Simon MARCHETTO
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
// =============================================================================
// <-- CLI SHELL MODE -->
path = SCI+"/modules/spreadsheet/tests/unit_tests/";
// =============================================================================
M = eye(3, 5);
//
filename = fullfile(TMPDIR,"M_1.csv");
csvWrite(M, filename);
assert_checkfilesequal ( filename , fullfile(path,"M_1.csv") );
//
filename = fullfile(TMPDIR,"M_2.csv");
csvWrite(M, filename, ascii(9));
assert_checkfilesequal ( filename , fullfile(path,"M_2.csv") );
//
filename = fullfile(TMPDIR,"M_3.csv");
csvWrite(M, filename, " ", ",");
assert_checkfilesequal ( filename , fullfile(path,"M_3.csv") );
//
filename = fullfile(TMPDIR,"M_4.csv");
csvWrite(M, filename, ";", ",");
assert_checkfilesequal ( filename , fullfile(path,"M_4.csv") );
// =============================================================================
N = [%nan , 1, %nan ; -%inf , %inf, 4];
//
filename = fullfile(TMPDIR,"N_1.csv");
csvWrite(N, filename);
assert_checkfilesequal ( filename , fullfile(path,"N_1.csv") );
//
filename = fullfile(TMPDIR,"N_1.csv");
csvWrite(N, filename, ascii(9));
assert_checkfilesequal ( filename , fullfile(path,"N_2.csv") );
//
filename = fullfile(TMPDIR,"N_1.csv");
csvWrite(N, filename, " ", ",");
assert_checkfilesequal (filename , fullfile(path,"N_3.csv") );
//
filename = fullfile(TMPDIR,"N_1.csv");
csvWrite(N, filename, ";", ",");
assert_checkfilesequal ( filename , fullfile(path,"N_4.csv") );
// =============================================================================
K = eye(3, 2) + 0.1;
//
filename = fullfile(TMPDIR,"K_1.csv");
csvWrite(K, filename);
assert_checkfilesequal ( filename , fullfile(path,"K_1.csv") );
//
filename = fullfile(TMPDIR,"K_2.csv");
csvWrite(K, filename, ascii(9));
assert_checkfilesequal ( filename , fullfile(path,"K_2.csv") );
//
filename = fullfile(TMPDIR,"K_3.csv");
csvWrite(K, filename, " ", ",");
assert_checkfilesequal ( filename , fullfile(path,"K_3.csv") );
//
filename = fullfile(TMPDIR,"K_4.csv");
csvWrite(K, filename, ";", ",");
assert_checkfilesequal ( filename , fullfile(path,"K_4.csv") );
// =============================================================================
S = [
    "Allan",                  "2", "CORNET";
    "csv read/write toolbox", "3", "for scilab"
];
//
filename = fullfile(TMPDIR,"S_1.csv");
csvWrite(S, filename, "|");
assert_checkfilesequal ( filename , fullfile(path,"S_1.csv") );
//
filename = fullfile(TMPDIR,"S_2.csv");
csvWrite(S, filename, ascii(9));
assert_checkfilesequal ( filename , fullfile(path,"S_2.csv") );
//
filename = fullfile(TMPDIR,"S_3.csv");
csvWrite(S, filename, "!", ",");
assert_checkfilesequal ( filename , fullfile(path,"S_3.csv") );
//
filename = fullfile(TMPDIR,"S_4.csv");
csvWrite(S, filename, ";", ",");
assert_checkfilesequal ( filename , fullfile(path,"S_4.csv") );
// =============================================================================
M = [%inf, %nan];
filename = fullfile(TMPDIR,"data.csv");
csvWrite(M, filename);
assert_checkfilesequal ( filename , fullfile(path,"data.csv") );
//
// =============================================================================
//
// Configure the comments
M = [1:4] * 0.1;
comm = [
"// Copyright (C) INRIA"
"//  This file must be used under the terms of the CeCILL."
];
filename = fullfile(TMPDIR,"test.csv");
csvWrite(M, filename,[],[],[],comm);
Mstr = mgetl(filename);
expected = [
"// Copyright (C) INRIA"
"//  This file must be used under the terms of the CeCILL."
"0.10000000000000001,0.20000000000000001,0.30000000000000004,0.40000000000000002"
];
assert_checkequal ( Mstr , expected );
// =============================================================================

// complex matrix
complexMatrix = [0.211, -3.14, 0; ..
1+0*%i, 40.78*%i, -4.53*%i; ..
5+%i, 5+3.5*%i, 67.0-15*%i; ..
-%inf, %inf+2*%i, %inf-5.0*%i; ..
%nan, %nan*%i, %nan+%nan*%i];

//TODO check values with %inf*%i (currently bug on interpreting %inf*%i)

filename = fullfile(TMPDIR, "complex.csv");
csvWrite(complexMatrix, filename, ascii(9), ".", "%5.3f");
assert_checkfilesequal(filename , fullfile(path, "complex.csv"));
