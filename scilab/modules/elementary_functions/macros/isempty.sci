// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 1998 - INRIA
// Copyright (C) DIGITEO - 2011-2012 - Allan CORNET
// Copyright (C) 2016 - Samuel GOUGEON
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function answ = isempty(m)

    if nargin <> 1 then
        error(71, 1)
    end

    m_type = type(m);

    select m_type
    case 1
        answ = m == [];
    case 10
        // matrix of character string
        answ = and(m == "");

    case 15
        // list
        answ = %t
        for e = m
            if ~(type(e)==0 || isempty(e))
                answ = %f
                break
            end
        end

    case 16
        // typed list
        if typeof(m) == "rational" then
            answ = size(m, "*") == 0;
        else
            answ = %t;
            for i = 2:size(m)
                e = m(i)
                if ~(type(e)==0 || isempty(e))
                    answ = %f
                    break
                end
            end
        end

    case 17
        // mlist
        if typeof(m)=="ce"      // array of cells
            if size(m,"*")==1
                answ = isempty(m{1})
            else
                answ = %t
                for i = 1:size(m,"*")
                    if ~isempty(m(i))
                        answ = %f
                        break
                    end
                end
            end

        elseif typeof(m)=="st"    // array of structures
            answ = %t
            fn = fieldnames(m)
            if size(m, "*")>0 && fn~=[]
                for f = fn(:)'
                    if ~isempty(m(f))
                        answ = %f
                        break
                    end
                end
            end
        else                    // other types of mlist
            answ = %f
        end

    else
        if( (m_type >= 11) & (m_type <= 13) | (m_type >= 128) ) then
            error(_("%s: Wrong type for input argument #%d."), "isempty", 1)
        elseif m_type~=0
            answ = size(m,"*")==0
        else
            answ = %t
        end
    end

endfunction
