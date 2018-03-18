// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ???? - INRIA
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function M=%p_i_s(varargin)
    M=varargin(nargin)
    N=varargin(nargin-1)//inserted matrix
    index=varargin(1)

    if nargin==3&(type(index)==10|type(index)==15) then
        M=createstruct(index,N)
        if type(index(1))<>10 & index(2)=="entries" then
            // change struct to cell
            f=getfield(1,M);f(1)="ce"
            M=setfield(1,f,M)
        end
    elseif nargin>4 then //more than 2 indices: insertion of a polynomial in an  matrix of numbers
        M=varargin($)
        M=matrix(M(:), size(M))
        varargin($)=M;
        M=generic_i_hm(0,varargin(:))
    else
        //should not occurs (hard coded case)
    end
endfunction
