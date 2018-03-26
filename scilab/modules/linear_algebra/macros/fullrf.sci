// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) ????-2008 - INRIA
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [Q,M,rk]=fullrf(A,tol)
    //[Q,M,rk]=fullrf(A)
    //Full rank factorization : A=Q.M
    //with range(Q)=range(A) and ker(M)=ker(A),
    //Q full column rank , M full row rank
    // rk = rank(A) = #columns(Q) = #rows(M)
    //F.D.
    //!
    na1=norm(A,1);
    if nargin==1 then tol=sqrt(%eps);end
    if na1 < 1.d-10 then Q=[];M=[];rk=0;return;end
    tol1=tol*na1;
    [U,s,V,rk]=svd(A,tol1);
    sq=sqrt(s);
    Q=U*sq;M=sq*V';
    Q=Q(:,1:rk);M=M(1:rk,:);
endfunction
