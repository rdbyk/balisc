// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2010 - Scilab Enterprises - Adeline CARNIS
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Samuel GOUGEON
// Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [m, k] = %sp_min(varargin)

    elements = varargin;
    error_list = "";

    // If the first argument is a list, it retrieves the number of sparse
    // matrices in list
    if type(varargin(1)) == 15 then
        if nargin <> 1 then
            msg = _("%s: Wrong size of input argument: %d expected.\n")
            error(msprintf(msg, "%sp_min", 1))
        end

        nargin = length(varargin(1))
        elements = varargin(1)
        error_list = _(" (in list)")

        // If the second argument of list is not a sparse -> ERROR
        if nargin == 2 & type(elements(2)) <> 5 then
            msg = _("%s: Wrong type for input argument #%d: A sparse matrix expected.\n")
            error(msprintf(msg, "%sp_min", 1))
        end
    end

    A1 = elements(1);   // Is necessarily a sparse, due to the %sp_ prefix
    // Check if A1 is real
    if ~isreal(A1) then
        msg = _("%s: Argument #%d: Complex numbers not supported.\n")
        error(msprintf(msg, "%sp_min", 1));
    end
    siz = size(A1);

    // min(A)
    // ------
    if nargin==1
        if isempty(A1) then
            m = []
            k = []
            return
        end
        // Retrieves entries of sparse matrix
        [ij, v, mn] = spget(A1)

        // Matrix of zeros:
        if v==[] then
            m = 0
            k = 1
        else
            [m, k] = min(v);
            k = ij(k,:)
            if m>0 then
                i = find(A1(:)==0,1)
                if i~=[]
                    m = 0
                    k = i
                end
            end
        end
        if length(m)<2
            m = full(m)
        end
        if mn(1)>1 & mn(2)>1 & length(k)==1
            k = ind2sub(siz, k)
        elseif length(k)==2
            k = sub2ind(siz,k)
        end

    // min(A, "r"|"c"|"m")
    // -------------------
    elseif nargin==2 & type(elements(2))==10
        if isempty(A1) then
            m = A1
            k = []
            return
        end
        opts = elements(2);
        if ~or(opts==["c","r","m"]) then
            msg = _("%s: Wrong value for input argument #%d: [''r'' ''c'' ''m''] expected.\n")
            error(msprintf(msg, "%sp_min", 2))
        end
        if or(opts==["r" "m"])
            A1 = A1'
        end
        [ij, v, mn] = spget(A1)
        m = spzeros(mn(1), 1)
        k = ones(mn(1), 1)
        ind = gsort([ij(:,1) v ij(:,2)], "lr", "i") // Row  Val  Col
        [tmp, kk] = unique(ind(:,1))
        tab = ind(kk,:)
        [i v K] = (tab(:,1), tab(:,2), tab(:,3))
        ind = find(v>0)
        for j = ind
            kk = find(A1(i(j),:)==0,1)
            if kk ~= []
                v(j) = 0
                K(j) = kk
            end
        end
        m(i) = v
        k(i) = K
        // If opts = 'r' or 'm', the result is returned in row vector
        if or(opts==["r" "m"]) then
            m = m'
            k = k'
        end

    // min(A1,A2,...) or equivalently min(list(A1,A2,..))
    // --------------------------------------------------
    else
        // m is the first matrix
        m = elements(1);
        if nargout > 1
            k = ones(m)
        end
        [m1, n1] = size(m)
        // Loop on the number of input arguments
        for i = 2:nargin
            An = elements(i);
            // Check if An is a sparse
            if and(type(An) <> [1 5])  | (type(An)==1 & or(size(An)~=[1 1])) then
                msg = _("%s: Wrong type for input argument #%d%s: A sparse matrix or a scalar expected.\n")
                error(msprintf(msg, "%sp_min", i, error_list))
            end
            // Check if An is real
            if ~isreal(An) then
                msg = _("%s: Argument #%d%s: Complex numbers not supported.\n")
                error(msprintf(msg, "%sp_min", i, error_list))
            end
            [m2, n2] = size(An)
            // Check size
            if (m1 <> m2 | n1 <> n2) & or([m2 n2]~=[1 1]) then
                msg = _("%s: Wrong size of input argument #%d%s: Same size as input argument #%d expected.\n")
                error(msprintf(msg, "%sp_min", i, error_list, 1))
            end
            // If An is a scalar: check that it is positive
            if and([m2 n2]==[1 1]) & An<0 then
                msg = _("%s: Argument #%d: the scalar must be positive.\n")
                error(msprintf(msg, "%sp_max", i))
            end
            // Processing:
            mNan = isnan(m);
            newNan = isnan(An);
            pos = (m > An) | (mNan & ~newNan) | ..
                  (mNan & newNan) // position of the last %nan, as with dense processing
            if or([m2 n2]~=[1 1])
                m(pos) = An(pos)
            else
                m(pos) = An
            end
            if nargout > 1
                k(pos) = i
            end
        end  // for
        if length(m)<2
            m = full(m)
        end
    end
endfunction
