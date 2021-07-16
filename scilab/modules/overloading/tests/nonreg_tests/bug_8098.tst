// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

// <-- Non-regression test for bug 8098 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=8098
//
// <-- Short Description -->
//    cumsum() did not apply to rational matrices.
// =============================================================================

s = poly(0, "s");
r = [1/s 1/s; 1/s^2 1];

assert_checkequal(cumsum(r), [1 1+2*s;1+s 1+2*s+s^2]./[s s^2;s^2 s^2]);
assert_checkequal(cumsum(r,"*"), [1 1+2*s;1+s 1+2*s+s^2]./[s s^2;s^2 s^2]);
assert_checkequal(cumsum(r, 1), [1 1;1+s 1+s]./[s s;s^2 s]);
assert_checkequal(cumsum(r, 2), [1 2;1 1+s^2]./[s s;s^2 s^2]);
assert_checkequal(cumsum(r, "r"), [1 1;1+s 1+s]./[s s;s^2 s]);
assert_checkequal(cumsum(r, "c"), [1 2;1 1+s^2]./[s s;s^2 s^2]);
assert_checkequal(cumsum(r, "m"), [1 1;1+s 1+s]./[s s;s^2 s]);
assert_checkequal(cumsum(r,"native"), [1 1+2*s;1+s 1+2*s+s^2]./[s s^2;s^2 s^2]);
assert_checkequal(cumsum(r,"double"), [1 1+2*s;1+s 1+2*s+s^2]./[s s^2;s^2 s^2]);
assert_checkequal(cumsum(r,"*", "native"), [1 1+2*s;1+s 1+2*s+s^2]./[s s^2;s^2 s^2]);
assert_checkequal(cumsum(r, 1, "native"), [1 1;1+s 1+s]./[s s;s^2 s]);
assert_checkequal(cumsum(r, 2, "native"), [1 2;1 1+s^2]./[s s;s^2 s^2]);
assert_checkequal(cumsum(r, "r", "native"), [1 1;1+s 1+s]./[s s;s^2 s]);
assert_checkequal(cumsum(r, "c", "native"), [1 2;1 1+s^2]./[s s;s^2 s^2]);
assert_checkequal(cumsum(r, "m", "native"), [1 1;1+s 1+s]./[s s;s^2 s]);
assert_checkequal(cumsum(r,"*", "double"), [1 1+2*s;1+s 1+2*s+s^2]./[s s^2;s^2 s^2]);
assert_checkequal(cumsum(r, 1, "double"), [1 1;1+s 1+s]./[s s;s^2 s]);
assert_checkequal(cumsum(r, 2, "double"), [1 2;1 1+s^2]./[s s;s^2 s^2]);
assert_checkequal(cumsum(r, "r", "double"), [1 1;1+s 1+s]./[s s;s^2 s]);
assert_checkequal(cumsum(r, "c", "double"), [1 2;1 1+s^2]./[s s;s^2 s^2]);
assert_checkequal(cumsum(r, "m", "double"), [1 1;1+s 1+s]./[s s;s^2 s]);

// Check error
assert_checkerror("cumsum(r, ""toto"")", [], 110);

a = cumsum([1/%z %z/(1+2*%z)]);
assert_checkequal(a, [1/%z (1+2*%z+%z^2)/(%z+2*%z^2)]);

a = cumsum([1/%z %z/(1+2*%z)]');
assert_checkequal(a, [1/%z (1+2*%z+%z^2)/(%z+2*%z^2)]');
