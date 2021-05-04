// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - Samuel GOUGEON
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//
// <-- Non-regression test for bug 8356 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=8356
//
// <-- Short Description -->
// sci2exp() applied to a list having undefined fields yielded an error
// sci2exp() applied to tlists or mlists having undefined fields gave wrong results

format("v",10);
L = list(%pi, –, "Hello");
m = mlist(["test","a","b","c"], –, 3.1415927, –, –,"Hello");
t = tlist(["test" "a" "b" "c"], %pi, –, %z);
assert_checkequal(sci2exp(L), "list(3.1415927,void(),""Hello"")");
assert_checkequal(sci2exp(L,15), ["list(3.1415927,..";"void(),""Hello"")"]);
assert_checkequal(sci2exp(t), "tlist([""test"",""a"",""b"",""c""],3.1415927,void(),%z)");
assert_checkequal(sci2exp(t,20), ["tlist(..";"[""test"",""a"",""b"",""c""],..";"3.1415927,void(),%z)"]);
assert_checkequal(sci2exp(m), "mlist([""test"",""a"",""b"",""c""],void(),3.1415927,void(),void(),""Hello"")");
assert_checkequal(sci2exp(m, 30), ["mlist([""test"",""a"",""b"",""c""],.."; "void(),3.1415927,void(),void(),..";"""Hello"")"]);

c = tlist(["test","b","u","t","L"],%t,–,"It works",list(%z,–,%i));
assert_checkequal(sci2exp(c), "tlist([""test"",""b"",""u"",""t"",""L""],%t,void(),""It works"",list(%z,void(),%i))");
r = ["tlist([""test"",""b"",""u"",""t"",""L""],%t,void(),.."
     """It works"",list(%z,void(),%i))"
     ];
assert_checkequal(sci2exp(c,40),r);
