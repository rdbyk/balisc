// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2007-2008 - INRIA - Pierre MARECHAL <pierre.marechal@inria.fr>
// Copyright (C) 2021 - Dirk Reusch, Kybernetik Dr. Reusch
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->
// <-- NO CHECK ERROR OUTPUT -->

dt = getdate(0);
if dt(1) <> [1970, 1969] then pause,end
if dt(2) <> [1, 12]      then pause,end
if dt(3) <> 1            then pause,end
if dt(4) <> [1, 365]     then pause,end
if dt(5) <> [5, 4]       then pause,end
if dt(6) <> [1, 31]      then pause,end
// if dt(7) <> 1 then pause,end // timezone dependent
if dt(8) <> 0 then pause,end
if dt(9) <> 0 then pause,end
if dt(10) <> 0 then pause,end

dt = getdate(1);
if dt(1) <> [1970, 1969] then pause,end
if dt(2) <> [1, 12]      then pause,end
if dt(3) <> 1            then pause,end
if dt(4) <> [1, 365]     then pause,end
if dt(5) <> [5, 4]       then pause,end
if dt(6) <> [1, 31]      then pause,end
// if dt(7) <> 1 then pause,end // timezone dependent
if dt(8) <> 0 then pause,end
if dt(9) <> 1 then pause,end
if dt(10) <> 0 then pause,end

dt = getdate(90542256);
if dt(1) <> 1972       then pause,end
if dt(2) <> 11         then pause,end
if dt(4) <> [318, 319] then pause,end
if dt(5) <> [2, 3]     then pause,end
if dt(6) <> [13, 14]   then pause,end
// if dt(7) <> 23 then pause,end // timezone dependent
if dt(8) <> 37 then pause,end
if dt(9) <> 36 then pause,end
if dt(10) <> 0 then pause,end


tzoffset = getdate(0)(7);

if tzoffset >= 0 && tzoffset <= 2 then
    t1_ref = getdate("s");
    t2_ref = datenum();
    t3_ref = getdate();

    t1 = t1_ref;
    t2 = (t2_ref - datenum(1970,1,1,1,0,0)) *3600*24;
    t3 = (datenum(t3_ref(1),t3_ref(2),t3_ref(6),t3_ref(7),t3_ref(8),t3_ref(9)) - datenum(1970,1,1,1,0,0)) * 3600 * 24;

    if ((abs(t2-t1) > 1) & (abs(t2-t1)-3600 > 1))  then pause,end
    if ((abs(t3-t1) > 1) & (abs(t3-t1)-3600 > 1))  then pause,end
    if ((abs(t3-t2) > 1) & (abs(t3-t2)-3600 > 1))  then pause,end
end

assert_checkerror("getdate(-1)", [], 110);
assert_checkerror("getdate(%i)", [], 94);
