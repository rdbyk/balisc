// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA
// Copyright (C) 2010 - DIGITEO - Bruno JOFRET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

//exists

// []
assert_checkequal(exists([]),[]);
assert_checkequal(exists([],"a"), []);
assert_checkequal(exists([],"l"), []);
assert_checkequal(exists([],"n"), []);

a=1;
assert_checkequal(exists('a'), 1);
clear a;
assert_checkequal(exists('a'), 0);

a=1; b=1;
assert_checkequal(exists(['a', 'b']), [1, 1]);
assert_checkequal(exists(['a'; 'b']), [1; 1]);
assert_checkequal(exists(['a', 'b'; 'a', 'b']), [1, 1; 1, 1]);
clear b;
assert_checkequal(exists(['a', 'b']), [1, 0]);
assert_checkequal(exists(['a'; 'b']), [1; 0]);
assert_checkequal(exists(['b', 'a']), [0, 1]);
assert_checkequal(exists(['b'; 'a']), [0; 1]);
assert_checkequal(exists(['a', 'b'; 'a', 'b']), [1, 0; 1, 0]);
clear a;
assert_checkequal(exists(['a', 'b']), [0, 0]);
assert_checkequal(exists(['a'; 'b']), [0; 0]);
assert_checkequal(exists(['a', 'b'; 'a', 'b']), [0, 0; 0, 0]);

function __check_exists__(scope, x)
  assert_checkequal(exists("a", scope), 1);
endfunction

function __check_exists2__(scope, x)
    a=42; b=42;
    assert_checkequal(exists(['a', 'b'], scope), [1, 1]);
    assert_checkequal(exists(['a'; 'b'], scope), [1; 1]);
    assert_checkequal(exists(['a', 'b'; 'a' 'b'], scope), [1, 1; 1, 1]);
endfunction

function __check_not_exists__(scope, x)
  assert_checkequal(exists("a", scope), 0);
endfunction

function __check_not_exists2__(scope, x)
    a=51; b=51;
    assert_checkequal(exists(['a', 'b'], scope), [0, 0]);
    assert_checkequal(exists(['a'; 'b'], scope), [0; 0]);
    assert_checkequal(exists(['a', 'b'; 'a', 'b'], scope), [0, 0; 0, 0]);
endfunction

// Define a ONLY in calling scope
a = 42; b=42;
__check_exists__("all", []);
__check_exists__("nolocal", []);
__check_not_exists__("local", []);
clear a; clear b;

// Define a ONLY in function local scope
__check_exists__("all", a = 42);
__check_exists__("local", a = 42);
__check_not_exists__("nolocal", a = 42);
__check_exists2__("all", []);
__check_exists2__("local", []);
__check_not_exists2__("nolocal", []);

// Define a BOTH in calling and local scope
a = 42; b=42;
__check_exists__("all", a = 51);
__check_exists__("local", a = 51);
__check_exists__("nolocal", a = 51);
__check_exists2__("all", []);
__check_exists2__("local", []);
__check_exists2__("nolocal", []);
clear a; clear b;
