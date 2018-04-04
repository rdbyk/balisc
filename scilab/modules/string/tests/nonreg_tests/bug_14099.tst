// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Samuel GOUGEON
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// <-- CLI SHELL MODE -->
// <-- Non-regression test for bug 14099 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/14099
//
// <-- Short Description -->
// string(polynomial) and string(rational) had badly formatted outputs
//  and were not vectorized
//
// * Coefficients equal to +1|-1 were not masked: 1x^n  =>  x^n
// * Coefficients with imaginary parts were output as "%i*##": =>"##i"
// * Pure imaginary coefficients had parentheses: (%i*3)z^n  => 3iz^n
// * format("e") was as well applied to exponents: 3.4D+04x^2.0D+00 => 3.4D+04x^2

format("v", 10);

// Single polynomials
    // Constantes
assert_checkequal(string(0*%z), ["";"0"]);
assert_checkequal(string(0*%i*%z), ["";"0"]);
assert_checkequal(string(3+0*%z), ["";"3"]);
assert_checkequal(string(-3+0*%z), ["";"- 3"]);

assert_checkequal(string(3*%i+0*%z), ["";"3i"]);
assert_checkequal(string(-3*%i+0*%z), ["";"- 3i"]);

assert_checkequal(string(1-3*%i+0*%z), ["";"(1-3i)"]);
assert_checkequal(string(-1+3*%i+0*%z), ["";"- (1-3i)"]);
assert_checkequal(string(-1-3*%i+0*%z), ["";"- (1+3i)"]);
    //
assert_checkequal(string(-3*%i*%z), ["";"- 3iz"]);
assert_checkequal(string((1-3*%i)*%z), ["";"(1-3i)z"]);
assert_checkequal(string((-1+3*%i)*%z), ["";"- (1-3i)z"]);
assert_checkequal(string((-1-3*%i)*%z), ["";"- (1+3i)z"]);

assert_checkequal(string(-3*%i*%z^13), ["     13";"- 3iz"]);
assert_checkequal(string((1-3*%i)*%z^13), ["       13";"(1-3i)z"]);
assert_checkequal(string((-1+3*%i)*%z^13), ["         13";"- (1-3i)z"]);
assert_checkequal(string((-1-3*%i)*%z^13), ["         13";"- (1+3i)z"]);

p = (1-%i) - %i*%z -3*%i*%z^8 + 4*%z^15 - %i*%z^18;
assert_checktrue(and(string(p)==["                8    15   18"; "(1-i) - iz - 3iz + 4z - iz"]));

p = - %i*%z -3*%i*%z^8 + 4*%z^15 - %i*%z^18;
assert_checktrue(and(string(p)==["          8    15   18"; "- iz - 3iz + 4z - iz"]));

// Matrix of polynomials
ps = "[0*z, 3+0*%i*z; -z, -%i*z;  -z^17, -%i*z^17;  "+..
     "1-z+5*z^3+41*z^20, (1+(1-%i)*z)^3-1;  "+..
     "-z+z^3+3*z^4, (%i-2)-3*z-3*%i*z^13+(1+7*%i)*z^20; ]";
z = poly(0,"x");
p = evstr(ps);
refS = [" "                   " "
        "0"                   "3"
        "   "                 "    "
        "- x"                 "- ix"
        "   17"               "    17"
        "- x"                 "- ix"
        "          3     20"  "             2         3"
        "1 - x + 5x + 41x"    "(3-3i)x - 6ix - (2+2i)x"
        "       3    4"       "                  13        20"
        "- x + x + 3x"        "- (2-i) - 3x - 3ix + (1+7i)x"
        ];
assert_checktrue(and(string(p)==refS));

x = poly(0,"x");
p = "[64.692+38.966*x-36.580*x^2+90.044*x^3-93.111*x^4;64.381-74.963*x+52.75*x^2-1.8822*x^3+32.721*x^4]";
p = evstr(p);
format(6);
refS = ["                       2        3        4"
        "64.69 + 38.97x - 36.58x + 90.04x - 93.11x"
        "                       2        3        4"
        "64.38 - 74.96x + 52.75x - 1.882x + 32.72x"
       ];
assert_checktrue(and(string(p)==refS));

p = p/3+p*%i/4;
format(5);
refS = ["                                            2               3               4"
        "(21.6+16.2i) + (13.0+9.74i)x - (12.2+9.14i)x + (30.0+22.5i)x - (31.0+23.3i)x"
        "                                            2               3               4"
        "(21.5+16.1i) - (25.0+18.7i)x + (17.6+13.2i)x - (0.63+0.47i)x + (10.9+8.18i)x"
        ];
assert_checktrue(and(string(p)==refS));

// with %nan and %inf
p = poly([%nan 2 3 -%nan 8],"x","coeff");
p = p+%i*p/2;
//""""+string(p)+""""
refS = ["                               2             3         4"
        "(Nan+Nani) + (2+i)x + (3+1.5i)x + (Nan+Nani)x + (8+4i)x"
        ];
assert_checktrue(and(string(p)==refS));

// with format("e")
format("e",8);
ps = "[0*z, 3+0*%i*z; -z, -%i*z;"+..
     "1+5*z^3-%pi*z^17,  -z^17; "+..
     "(1+(1-%i)*z)^3-1+%e*%i*z^11, -%i*z^17]";
z = poly(0,"x");
p = evstr(ps);
if getos()=="Windows" then // The exponential notation may depend on the OS
    refS = [" "                                                                        "       "
            "0"                                                                        "3.0D+00"
            "   "                                                                      "    "
            "- x"                                                                      "- ix"
            "                  3          17"                                          "   17"
            "1.0D+00 + 5.0D+00x - 3.1D+00x"                                            "- x"
            "                                 2                       3           11"  "    17"
            "(3.0D+00 - 3.0D+00i)x - 6.0D+00ix - (2.0D+00 + 2.0D+00i)x + 2.7D+00ix"    "- ix"
            ];
    assert_checktrue(and(string(p)==refS));
end

// With a name of variable longer than 1 character:
x = poly(0,"ABC");
p = (2-%i+x).^[2 4 ; 1 3];
format("v",10);
//""""+string(p)+""""
refS = ["                        2"  "                                    2           3     4"
        "(3-4i) + (4-2i)ABC + ABC"   "- (7+24i) + (8-44i)ABC + (18-24i)ABC + (8-4i)ABC + ABC"
        "           "                "                                2     3"
        "(2-i) + ABC"                "(2-11i) + (9-12i)ABC + (6-3i)ABC + ABC"
       ];
assert_checktrue(and(string(p)==refS));

