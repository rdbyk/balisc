// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - Scilab Enterprises - Sylvestre Ledru
// Copyright (C) 2016, 2017 - Samuel GOUGEON
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// When one or several new sizes are 0, [] is returned:
m = grand(3,4,"uin",0,100);
assert_checkequal(resize_matrix(m, [0 2]), []);
assert_checkequal(resize_matrix(m, [0 5]), []);
assert_checkequal(resize_matrix(m, [0 -1]), []);
assert_checkequal(resize_matrix(m, [2 0]), []);
assert_checkequal(resize_matrix(m, [4 0]), []);
assert_checkequal(resize_matrix(m, [-1 0]), []);
assert_checkequal(resize_matrix(m, [0 0]), []);

m = grand(3,4,2,"uin",0,100);
assert_checkequal(resize_matrix(m, [0 2 3]), []);
assert_checkequal(resize_matrix(m, [5 0 1]), []);
assert_checkequal(resize_matrix(m, [4 4 0]), []);
assert_checkequal(resize_matrix(m, [0 4 0]), []);
assert_checkequal(resize_matrix(m, [0 0 0]), []);

// Every new size <0 is kept as is:
m = grand(3,4,"uin",0,100);
assert_checkequal(size(resize_matrix(m, [-1 2])), [3 2]);
assert_checkequal(size(resize_matrix(m, [-1 5])), [3 5]);
assert_checkequal(size(resize_matrix(m, [-1 5 2])), [3 5 2]);
assert_checkequal(size(resize_matrix(m, [2 -1])), [2 4]);
assert_checkequal(size(resize_matrix(m, [5 -1])), [5 4]);
assert_checkequal(size(resize_matrix(m, [2 -1 2])), [2 4 2]);
assert_checkequal(size(resize_matrix(m, [-1 -1 2])), [3 4 2]);
m = grand(3,4,2,"uin",0,100);
assert_checkequal(size(resize_matrix(m, [-1 5 3])), [3 5 3]);
assert_checkequal(size(resize_matrix(m, [2 -1 3])), [2 4 3]);
assert_checkequal(size(resize_matrix(m, [2 5 -1])), [2 5 2]);
assert_checkequal(size(resize_matrix(m, [-1 -1 3])), [3 4 3]);
assert_checkequal(size(resize_matrix(m, [-1 3 -1])), [3 3 2]);
assert_checkequal(size(resize_matrix(m, [2 -1 -1])), [2 4 2]);
assert_checkequal(size(resize_matrix(m, [-1 3 -1])), [3 3 2]);
m = grand(3,4,2,2,"uin",0,100);
assert_checkequal(size(resize_matrix(m, [-1 3 3 -1])), [3 3 3 2]);

// Trailing singletons at dims>2 are removed:
m = grand(3,4,2,2,"uin",0,100);
assert_checkequal(size(resize_matrix(m, [-1 3 3 1])), [3 3 3]);
assert_checkequal(size(resize_matrix(m, [-1 3 1 1])), [3 3]);

// -----------
myMat =[     0.6029980    4.2470508    3.2442814    3.7427533
1.4276821    2.6285304    4.9615955    2.0520295
4.3037573    4.9656049    0.2502099    3.0422632  ];

myMat = resize_matrix( myMat, 3, 3 ); // reduce the matrix size
refMat=[0.602998,4.2470508,3.2442814;
1.4276821,2.6285304,4.9615955;
4.3037573,4.9656049,0.2502099];

assert_checkequal(size(myMat), size(refMat));

assert_checkequal(myMat, refMat);

// With encoded integers:
itypes = [1 2 4 8 11 12 14 18];
refMat=[
0, 4, 3, 0
1, 2, 4, 0
4, 4, 0, 0
0, 0, 0, 0];
for i = itypes
    ref = iconvert(refMat,i);
    stype = typeof(ref);
    myMatInteger = resize_matrix( myMat, 4, 4, stype ); // create an integer matrix
    assert_checkequal(myMatInteger, ref);
end

// With booleans:
refMat = int32(refMat);
booleanMat=resize_matrix( refMat, 3, 5 , "boolean");
assert_checkequal(booleanMat, [%f %t %t %f %f; %t %t %t %f %f; %t %t %f %f %f]);

myMatBoolean = resize_matrix( myMat, 2, 2, "boolean" );
assert_checkequal(myMatBoolean, [%t %t; %t %t] );
assert_checkequal(size(myMatBoolean), [2, 2]);
myMatBoolean = resize_matrix( myMatBoolean, 3, 5 );
assert_checkequal(myMatBoolean, [%t %t %f %f %f; %t %t %f %f %f; %f %f %f %f %f]);
assert_checkequal(size(myMatBoolean), [3, 5]);

myMatBoolean(1:4:9) = %t;
myMatBoolean = resize_matrix(myMatBoolean, 3, 3);
assert_checkequal(myMatBoolean, [%t %t %f; %t %t %f; %f %f %t]);

// string matrix
myMatString = ["Scilab","the";"Open Source","Scientific";"Software","Package"];
myMatString = resize_matrix( myMatString, 3, 1 );

assert_checkequal(myMatString, ["Scilab";"Open Source";"Software"]);
