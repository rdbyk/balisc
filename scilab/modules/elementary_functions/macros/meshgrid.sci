// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA - Farid BELAHCENE
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function  varargout=meshgrid(varargin)

    if nargout>3 then
        error(_("%s: Wrong number of output arguments: At most %d expected."), "meshgrid", 3);
    elseif nargin>3 then
        error(_("%s: Wrong number of input arguments: At most %d expected."), "meshgrid", 3);
    end

    if or(nargout==[1 2]) & nargin==1 then
        [x,y]=ndgrid(varargin(1),varargin(1));
        varargout(1)=x';
        if nargout==2
            varargout(2)=y';
        end
    elseif or(nargout==[1 2]) & nargin==2 then
        [x,y]=ndgrid(varargin(:));
        varargout(1)=x';
        if nargout==2
            varargout(2)=y';
        end
    elseif nargout==3 & nargin==3 then
        [x,y,z]=ndgrid(varargin(:));
        varargout(1)=permute(x,[2,1,3]);
        if nargout>1
            varargout(2)=permute(y,[2,1,3]);
        end
        if nargout>2
            varargout(3)=permute(z,[2,1,3]);
        end
    else
        error(_("%s: Wrong number of output arguments vs. input arguments: Same number expected."),"meshgrid");
    end

endfunction
