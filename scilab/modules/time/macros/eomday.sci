// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA - Pierre MARECHAL
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

// Returns the last day of the year and month by corresponding element of Matrix Y and M

function E=eomday(Y,M)

    if nargin <> 2 then
        error(71, 2);
    end

    common_year = [31,28,31,30,31,30,31,31,30,31,30,31];
    leap_year   = [31,29,31,30,31,30,31,31,30,31,30,31];

    if type(Y) <> 1 | ~isreal(Y) | int(Y) <> Y then
        error(111, 1);
    end

    if type(M) <> 1 | ~isreal(M) | int(M) <> M then
        error(111, 2);
    end

    if or(size(Y) <> size(M)) then
        error(msprintf(gettext("%s: Wrong size for input arguments #%d and #%d: Same sizes expected.\n"),"eomday", 1, 2));
    end

    if (min(M) < 1) | (max(M) > 12) then
        error(110, 2, _("value between 1 and 12"));
    end

    [nr,nc] = size(M);
    E = zeros(1, nr*nc);
    isleapyear = isLeapYear(Y);
    E(isleapyear) = leap_year(M(isleapyear));
    E(~isleapyear) = common_year(M(~isleapyear));
    E = matrix(E,nr,nc);

endfunction
