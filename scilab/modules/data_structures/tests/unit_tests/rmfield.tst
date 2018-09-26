// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
//

s=struct("a",1,"b",2,"c",3,"d",4)

rmfield("b",s)
assert_checkfalse(isfield(s,"b"))

rmfield(["a","c"],s)
assert_checkfalse(isfield(s,"a"))
assert_checkfalse(isfield(s,"c"))

rmfield("dd",s)
assert_checktrue(isfield(s,"d"))

rmfield("d",s)
assert_checkfalse(isfield(s,"d"))
