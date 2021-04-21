// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2009 - DIGITEO - Allan CORNET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

//ouvrir le fichier 
FLN = 'SCI/modules/fileio/tests/unit_tests/text.txt';

fd = mopen(FLN,'rt'); 
i = 0;
while ~meof(fd) do
   mfscanf(1, fd, "%c");
   i = i + 1;
end

mclose(fd);

if i <> 1479 then pause,end

ierr = execstr('meof(0)','errcatch');
if ierr <> 50 then pause,end

ierr = execstr('meof(5)','errcatch');
if ierr <> 50 then pause,end

ierr = execstr('meof(6)','errcatch');
if ierr <> 50 then pause,end
