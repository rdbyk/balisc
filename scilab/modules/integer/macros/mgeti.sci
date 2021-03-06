// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Cedric Delamarre
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function x = mgeti(varargin)

    if nargin == 0 | nargin > 3 then
        error(72, 1, 3);
    end

    if nargin == 1 then
        typeToConvert = 4;
    else
        type = varargin(2);

        if typeof(type) <> "string" then
            error(91, 2);
        end

        if size(type, '*') <> 1 then
            error(102, 2);
        end

        typeToConvert = 0;
        len = length(type);
        partPos = 1;

        if len == 0 | len > 3 then
            error(100, 2, _("string of size 1 to 3"), "mgeti", 2, 1, 3);
        end

        // unsigne
        if part(type, partPos) == 'u'
            typeToConvert = 10;
            partPos = 2;
        end

        // type to convert
        select part(type, partPos)
        case 'l'
            typeToConvert = typeToConvert + 8;
        case 'i'
            typeToConvert = typeToConvert + 4;
        case 's'
            typeToConvert = typeToConvert + 2;
        case 'c'
            typeToConvert = typeToConvert + 1;
        else
            error(msprintf(_("%s: Incorrect integer type: %s .\n"), "mgeti", part(type, partPos)));
        end
    end

    x = iconvert(mget(varargin(:)), typeToConvert);
endfunction
