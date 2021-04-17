// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2015 - Scilab Enterprises - Paul Bignier
// Copyright (C) 2017 - Scilab Enterprises - Clement DAVID
// Copyright (C) 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- XCOS TEST -->
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//

b = scicos_block();
assert_checktrue(and(b==b));

d = scicos_diagram();
assert_checktrue(and(d==d));

l = scicos_link();
assert_checktrue(and(l==l));

assert_checkfalse(b==l);
assert_checkfalse(b==d);
assert_checkfalse(d==l);

// Just modifying 'graphics'
b2 = b;
b2.graphics.sz = [50 50];
resRef = [%t %f %t %t %t];
assert_checkequal(b==b2, resRef);

// 'graphics', 'model' and 'gui' differ
Sum = BIGSOM_f("define");
resRef = [%t %f %f %f %t];
assert_checkequal(b==Sum, resRef);

// 'props' and 'objs' differ
d2 = d;
d2.props.tf = 50;
d2.objs = list(Sum);
resRef = [%t %f %f %t %t];
assert_checkequal(d==d2, resRef);


// Now test '~='
assert_checkfalse(or(b~=b));
assert_checkfalse(or(d~=d));
assert_checkfalse(or(l~=l));

assert_checktrue(b~=l);
assert_checktrue(b~=d);
assert_checktrue(d~=l);

resRef = [%f %t %f %f %f];
assert_checkequal(b~=b2, resRef);

resRef = [%f %t %t %t %f];
assert_checkequal(b~=Sum, resRef);

resRef = [%f %t %t %f %f];
assert_checkequal(d~=d2, resRef);


// check with an object hierarchy

o1 = CLOCK_f("define");
o2 = CLOCK_f("define");
assert_checktrue(o1 == o2);

o1.model.rpar.objs(2).graphics.exprs = ["30" ; "0"];
assert_checkequal(o1 == o2, [%t %t %f %t %t]);

