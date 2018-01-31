//------------------------------------------------------------------------
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2005 - INRIA - Pierre MARECHAL
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [N,S] = weekday(D,form)

    if nargin < 1 | nargin > 2 then
        error(msprintf(gettext("%s: Wrong number of input arguments: %d or %d expected.\n"),"weekday",1,2));
    end

    if type(D) <> 1 then
        error(msprintf(gettext("%s: Wrong type  for input argument #%d: Real constant matrix expected.\n"),"weekday",1));
    end

    if (nargin==2) & (form <> "long") & (form <> "short") then
        error(msprintf(gettext("%s: Wrong value for input argument #%d: ''%s'' or ''%s'' expected.\n"),"weekday",2,"long","short"));
    end

    common_year  = [0,31,59,90,120,151,181,212,243,273,304,334,365];
    leap_year    = [0,31,60,91,121,152,182,213,244,274,305,335,366];
    week_numbers = [7,1,2,3,4,5,6];

    if nargin==2 && form == "long" then
        week_strings = [gettext("Saturday"), ..
                        gettext("Sunday")    , ..
                        gettext("Monday")    , ..
                        gettext("Tuesday")   , ..
                        gettext("Wednesday") , ..
                        gettext("Thursday")  , ..
                        gettext("Friday")    , ..
                        gettext("Jan")];
    else
        week_strings = [gettext("Sat"), ..
                        gettext("Sun"), ..
                        gettext("Mon"), ..
                        gettext("Tue"), ..
                        gettext("Wed"), ..
                        gettext("Thu"), ..
                        gettext("Fri")];
    end


    // Maurice Kraitchik Algorithm

    [nr,nc]  = size(D);

    if nc == 1 then
        common_year = common_year';
        leap_year   = leap_year';
    end

    month_day_mat   = ones(nr,nc);

    m               = ones(nr,nc);
    y               = ones(nr,nc);
    d               = ones(nr,nc);

    Y        = floor(D/365.2425);
    temp     = D - (365.0*Y + ceil(0.25*Y)- ceil(0.01*Y) + ceil(0.0025*Y));

    mask = find(temp <= 0);
    if mask <> []
        Y(mask)  = Y(mask) - 1;
        D(mask)  = D(mask) - (365.0*Y(mask) + ceil(0.25*Y(mask)) - ceil(0.01*Y(mask)) + ceil(0.0025*Y(mask)));
        D(~mask) = temp(~mask);
    else
        D = temp;
    end

    M = int(D/29);
    idx_leap_year = isLeapYear(Y);
    not_idx_leap_year = ~idx_leap_year;

    if M(idx_leap_year) <> []
        month_day_mat(idx_leap_year)  = leap_year(M(idx_leap_year)+1);
    end
    if M(not_idx_leap_year) <> []
        month_day_mat(not_idx_leap_year) = common_year(M(not_idx_leap_year)+1);
    end

    if M( D>month_day_mat ) <> [] then
        M( D>month_day_mat ) = M( D>month_day_mat )+1;
    end

    if M(idx_leap_year) <> []
        month_day_mat(idx_leap_year)  = leap_year(M(idx_leap_year));
    end

    if M(not_idx_leap_year) <> []
        month_day_mat(not_idx_leap_year) = common_year(M(not_idx_leap_year));
    end

    d = D - month_day_mat;

    m(M==1) = 13;
    m(M==2) = 14;

    if Y( M==1 | M==2 ) <> [] then
        y( M==1 | M==2 ) = Y( M==1 | M==2 ) - 1;
    end
    
    if M( M<>1 & M<>2 ) <> [] then
        m( M<>1 & M<>2 ) = M( M<>1 & M<>2 );
    end

    if Y( M<>1 & M<>2 ) <> [] then
        y( M<>1 & M<>2 ) = Y( M<>1 & M<>2 );
    end

    n =  modulo(  (d + floor(2*m) + floor(3*(m+1)/5) + y + floor(y/4) - floor(y/100) + floor(y/400) + 2)  ,  7  );

    N = matrix( week_numbers(n+1) , nr, nc );
    S = matrix( week_strings(n+1) , nr, nc );

endfunction
