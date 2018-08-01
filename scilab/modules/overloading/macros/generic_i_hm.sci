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

function M = generic_i_hm(default_value,varargin)

    //insertion of a matrix in an hypermatrix
    nargin=nargin-1
    M=varargin(nargin);
    N=varargin(nargin-1);//inserted matrix

    dims=matrix(size(M),-1,1);
    v=matrix(M,-1,1);

    nd=size(dims,"*")
    olddims=dims

    // adjust dimension of matrix M to number of indices
    reduced_index=%f
    if nargin-2>nd then
        dims(nd+1:nargin-2)=0;
    elseif nargin-2<nd  then //less indices than M number of dims
        dims=[dims(1:nargin-3);prod(dims(nargin-2:$))]
        if size(find(dims>1),"*")>1 then reduced_index=%t,end
    end

    //handling special case M(....)=[]
    if N==[] then
        // at most only one index should not match the full
        // corresponding dimension
        // if yes insertion is the extraction of the complement.
        ok=[];
        for k=1:nargin-2
            dk=varargin(k)
            if or(type(dk)==[2 129]) then
                dk=horner(dk,dims(k)),
            elseif type(dk)==4 then
                dk=find(dk)
            end
            if or(size(dk)<>-1) then
                dk=gsort(dk);
                if or(dk<>(dims(k):-1:1)) then
                    if dk(1)<1|dk($)>dims(k) then
                        error(msprintf(_("%s: Invalid index.\n"), "generic_i_hm"))
                    end
                    if ok<>[] then
                        msg = _("%s: A null assignment can have only one non-colon index.\n")
                        error(msprintf(msg, "generic_i_hm"));
                    end
                    ok=k
                    I1=1:dims(k);I1(dk)=[]
                    varargin(k)=I1
                end
            end

        end

        if size(ok,"*")==0 then
            M=[]
        else //use extraction
            [Ndims,I]=convertindex(dims,varargin(1:$-2));
            dims(ok)=size(I1,"*")
            while dims($)==1&size(dims,"*")>2, dims($)=[],end
            M=M(I);
            M=matrix(M, dims)
        end

        return
    end

    //convert N-dimensional indexes to 1-D and extend dims if necessary
    [Ndims,I]=convertindex(list(dims,size(N)),varargin(1:$-2));
    Ndims=matrix(Ndims,-1,1)

    //if reduced_index & or(Ndims<>dims), error(msprintf(_("%s: Invalid index.\n"), "generic_i_hm")), end
    if or(Ndims>dims) then
        //extend the destination matrix
        I1=0
        for k=size(Ndims,"*"):-1:1
            ik1=(1:dims(k))';
            if ik1<>[] then
                if Ndims(k)>1 then
                    if size(I1,"*")>1 then
                        I1=(Ndims(k)*I1).*.ones(ik1)+ones(I1).*.(ik1-1);
                    else
                        I1=Ndims(k)*I1+ik1-1;
                    end
                else
                    I1=Ndims(k)*I1+ik1-1;
                end
            end
        end
        // create the resulting matrix
        v2=[];v2(1:prod(Ndims),1)=default_value;
        // populate it with M entries
        if v<>[] then v2(I1+1)=v;end
    else
        v2=v
    end
    //insert N entries into result
    v2(I)=N(:)

    //remove trailing unitary dimensions
    if reduced_index then
        Ndims=olddims
    else
        while  Ndims($)==1 then Ndims($)=[],end
        select size(Ndims,"*")
        case 0 then
            Ndims=[1,1]
        case 1 then
            k=find(olddims<>1&olddims<>0)
            if k==[]|Ndims>prod(olddims) then //shape changed
                if oldEmptyBehaviour("query")=="off" then
                    Ndims=[1,Ndims]
                else
                    Ndims=[Ndims,1]
                end
            else
                Ndims=olddims;
            end
        else
            if N==[]
                Ndims=matrix(Ndims,1,-1)
            end
        end
    end
    M=matrix(v2,Ndims)
endfunction
