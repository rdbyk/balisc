// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2010 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

ierr = execstr("a=zzzzzzz", "errcatch");
assert_checkequal(ierr, 40);

[str, n] = lasterror();
assert_checkequal(ierr, 40);

ierr = execstr("a=zzzzzzz", "errcatch");
[str, n, l] = lasterror();
if l <> 1 then pause,end
assert_checkequal(ierr, 40);

ierr = execstr("a=zzzzzzz", "errcatch");
[str, n, l, f] = lasterror();
if l <> 1 then pause,end
if f <> '' then pause,end
assert_checkequal(ierr, 40);

ierr = execstr("a=zzzzzzz", "errcatch");
[str2, n2, l2, f2] = lasterror(%f);
if n2 <> n then pause,end
if l2 <> l then pause,end
if f2 <> f then pause,end
if str2 <> str then pause, end

[str3, n3, l3, f3] = lasterror(%t);
if n3 <> n2 then pause,end
if l3 <> l2 then pause,end
if f3 <> f2 then pause,end
if str <> str2 then pause, end

[str4, n4, l4, f4] = lasterror(%t);
if n4 <> 0 then pause,end
if l4 <> 0 then pause,end
if f4 <> '' then pause,end
if str4 <> [] then pause, end

ierr = execstr('a = lasterror(2);','errcatch');
assert_checkequal(ierr, 90);

ierr = execstr('a = lasterror([%t, %f]);','errcatch');
assert_checkequal(ierr, 90);
