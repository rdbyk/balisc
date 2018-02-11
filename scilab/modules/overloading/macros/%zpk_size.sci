// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - INRIA - Serge Steer
// Copyrigth (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// For more information, see the COPYING file which you should have received
// along with this program.

function [n,m]=%zpk_size(T,o)

    if  nargin==2 then
        if nargout<>1 then
            error(msprintf(_("%s: Wrong number of output argument: %d expected.\n"),"size",1))
        end
        n = size(T.K, o);
    else
        if nargout==1 then
            n = size(T.K)
        else
            [n,m] = size(T.K)
        end
    end

endfunction
