//<-- CLI SHELL MODE -->
// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

file1 = TMPDIR+'/test1.bin';
file2 = TMPDIR+'/test2.bin';
fd1 = mopen(file1,'wb');
fd2 = mopen(file2,'wb');
mput(1996,'ull',fd1);
mput(1996,'ull',fd2);
mclose(fd1);
mclose(fd2);

fd1 = mopen(file1,'rb');
if 1996<>mget(1,'ull',fd1) then
    write(%io(2),'Bug');
end
fd2 = mopen(file2,'rb');
if 1996<>mget(1,'ull',fd2) then
    write(%io(2),'Bug');
end
mclose(fd1);
mclose(fd2);
  
fd1 = mopen(file1,'rb');
 
assert_checkerror('mget([1 2],''ull'',fd2)', [], 93);
assert_checkerror('mget([1 2],''ull'',[fd2 fd2])', [], 93);
assert_checkerror('mget(''rrrr'',''ull'',[fd2 fd2])', [], 93);
assert_checkerror('mget(1,1,''fd2'')', [], 91);

mclose(fd1);
 
assert_checkerror('mget(1,''ull'',0)', [], 50);
assert_checkerror('mget(1,''ull'',6)', [], 50);
