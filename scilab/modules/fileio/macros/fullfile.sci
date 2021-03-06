// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA - Vincent COUVERT
// Copyright (C) DIGITEO - 2010-2012 - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function f = fullfile(varargin)

    if size(varargin) < 1 then
        error(74, 1);
    end

    fs = ["/" "\"];
    f  = varargin(1);

    if ~isempty(f) then
        if type(f) <> 10 then
            error(91, 1);
        end

        if size(f,"*") <> 1 then
            error(102, 1);
        end
        f = stripblanks(f);
    end

    nbParameters =  size(varargin)

    for k = 2 : nbParameters
        arg = varargin(k);
        if isempty(arg)
            // current arg is empty => nothing to do
            // f does not change
            continue;
        elseif isempty(f)
            // f is currently empty and arg as a value
            // check arg is a scalar string
            // and set f as arg
            if type(arg) <> 10 then
                error(91, k);
            end

            if (size(arg,"*") <> 1) && (k <> nbParameters) then
                error(102, k);
            end
            f = arg;
        else //arg and f are not empty
            if type(arg) <> 10 then
                error(91, k);
            end

            if (size(arg,"*") <> 1) && (k <> nbParameters) then
                error(102, k);
            end

            if or(part(f, length(f)) == fs) && or(part(arg, 1) == fs)
                f = f + stripblanks(part(arg, 2:length(arg)));
            elseif or(part(f, length(f))==fs) || or(part(arg, 1)==fs)
                f = f + stripblanks(arg);
            else
                f = f + filesep() + stripblanks(arg);
            end
        end
    end

    f = pathconvert(f, %f, %f);

endfunction
