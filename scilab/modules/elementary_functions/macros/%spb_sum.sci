// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2010 -  INRIA - Serge Steer
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function r=%spb_sum(varargin)

    a = varargin(1)
    dims = size(a);

    nargs = size(varargin);
    select nargs
    case 1
        d = "*";
        typ = "double";
    case 2
        if or(varargin(2) == ["native", "double"]) then
            d = "*";
            typ = varargin(2);
        else
            d = varargin(2);
            typ = "double";
        end
    case 3
        d = varargin(2);
        typ = varargin(3);
    else
        error(msprintf(_("%s: Wrong number of input arguments: %d to %d expected.\n"),"sum", 1, 3));
    end

    // Check second argument : d
    select type(d)
    case 1
        if size(d,'*') <> 1 then
            error(msprintf(_("%s: Wrong size for input argument #%d: A scalar expected.\n"),"sum", 2))
        end
        if int(d) <> d | d < 0 then
            error(msprintf(_("%s: Wrong value for input argument #%d: Integer >= %d expected.\n"),"sum", 2, 1))
        end
    case 10 
        if size(d,'*') <> 1 then
            error(msprintf(_("%s: Wrong size for input argument #%d: string expected.\n"),"sum",2))
        end
        if and(d<>["r","c","*","m"]) then
            error(msprintf(_("%s: Wrong value for input argument #%d: Must be in the set {%s}.\n"),..
            "sum",2,"""*"",""r"",""c"",""m"""))
        end
        pos = [1,2,0,find(dims>1,1)];
        d=pos(find(d==["r","c","*","m"]))
    else
        error(msprintf(_("%s: Wrong type for input argument #%d: string or scalar expected.\n"),"sum",2))
    end

    // Check third argument
    if type(typ)<>10 then
        error(msprintf(_("%s: Wrong type for input argument #%d: string expected.\n"),"sum",3))
    end

    if size(typ,"*")<>1 then
        error(msprintf(_("%s: Wrong size for input argument #%d: string expected.\n"),"sum",3))
    end

    if and(typ <> ["native" "double"]) then
        error(msprintf(_("%s: Wrong value for input argument #%d: ""%s"" or ""%s"" expected.\n"),"sum", 3, "native", "double"));
    end

    ij=spget(a);
    select d
    case 0 then
        //sum of all elements
        if typ=="native" then
            r=size(ij,1)<>0
        else
            r=size(ij,1)
        end
    case 1 then
        if typ=="native" then
            r(1,dims(2))=%f
            for k=1:dims(2)
                r(k)=or(ij(:,2)==k)
            end
        else
            r=zeros(1,dims(2));
            for k=1:dims(2)
                r(k)=size(find(ij(:,2)==k),"*")
            end
        end
        r=sparse(r)
    case 2 then
        if typ=="native" then
            r(dims(1),1)=%f
            for k=1:dims(1)
                r(k)=or(ij(:,1)==k)
            end
        else
            r=zeros(ndims(1),1);
            for k=1:dims(1)
                r(k)=size(find(ij(:,1)==k),"*")
            end
        end
        r=sparse(r)
    else
        if typ=="native" then
            r=a
        else
            r=sparse(ij,ones(size(ij,1),1),dims)
        end
    end

endfunction
