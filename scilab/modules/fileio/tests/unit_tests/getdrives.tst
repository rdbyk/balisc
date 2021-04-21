// ============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Bruno JOFRET
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// ============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

ierr = execstr("getdrives(0)", "errcatch");
if ierr <> 71 then pause,end

drives = getdrives();

if getos() == "Windows" then
    //
    // Windows part
    //
    // At least one letter
    if size(drives, '*') < 1 then pause,end
    for i=drives
      if isdir(i) == %f then pause,end
    end
else
    //
    // Linux and Mac
    //
    if size(drives, '*') <> 1 then pause,end
    if drives <> "/" then pause,end
    if isdir(drives) == %f then pause,end
end
