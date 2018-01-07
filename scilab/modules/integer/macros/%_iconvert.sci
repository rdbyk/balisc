// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Antoine ELIAS
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function x = %_iconvert(a,typeToConvert)

    if type(a) == 1 & isreal(a) == %f then
        error(msprintf(_("%s: Wrong type for argument #%d: Real matrix expected.\n"), "iconvert", 1));
    end

    if floor(typeToConvert) <> typeToConvert then
        error(msprintf(_("%s: Wrong value for input argument #%d: An integer value expected.\n"), "iconvert", 2));
    end

    if type(typeToConvert) <> 1 | size(typeToConvert, "*") <> 1 then
        error(msprintf(_("%s: Wrong size for argument #%d: Real scalar expected.\n"), "iconvert", 2));
    end

    select typeToConvert
    case 0 then
        x = double(a);
    case 1 then
        x = int8(a);
    case 2 then
        x = int16(a);
    case 4 then
        x = int32(a);
    case 8 then
        x = int64(a);
    case 11 then
        x = uint8(a);
    case 12 then
        x = uint16(a);
    case 14 then
        x = uint32(a);
    case 18 then
        x = uint64(a);
    else
        error(msprintf(_("%s: Wrong value for input argument #%d: Must be in the set {%s}.\n"), "iconvert", 2, "0, 1, 2, 4, 8, 11, 12, 14, 18"));
    end

endfunction
