// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2016 - INRIA - Serge Steer
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// <-- CLI SHELL MODE -->
// <-- NO CHECK REF -->

function [A11,A12,A21,A22]=split4(A,m,n)
  //m,n:taille du bloc 11
      i1 = 1:m;   j1 = 1:n;
      i2 = m+1:$; j2 = n+1:$;
      A11=A(i1,j1);A12=A(i1,j2);A21=A(i2,j1);A22=A(i2,j2);
endfunction
function S=check(P,p,R)
  if argn(2)==2 then
    R=p
    p=size(R')
  end
  [mp,np]=size(P)
  [mr,nr]=size(R)
  [P11,P12,P21,P22]=split4(P,mp-p(1),np-p(2));
  [R11,R12,R21,R22]=split4(R,p(2),p(1));
  D=eye()-P22*R11;
  S=[P11+P12*R11*(D\P21), (P12*R11*(D\P22)*R12)+P12*R12;
     R21*(D\P21),R21*((D\P22)*R12)+R22]
endfunction

// with simple gains
P=[1 2;3 4];R=2;
T=lft(P,R);
assert_checkalmostequal (T , -5/7 );
assert_checktrue(T==lft(P,[1,1],R));


P=[1 2 3; 4 5 6;7,8,9];R=[1 0;0 2];
T=lft(P,R);
assert_checkalmostequal (T ,-1);
assert_checktrue(T==lft(P,[2,2],R));

P=[1 2 3; 4 5 6;7,8,9];R=[1 0;0 2];
[T,t]=lft(P,[1,1],R);
assert_checkalmostequal (T ,[-13/8 -1 0;-5/4 -1 0;0 0 2]);
assert_checktrue(T==lft(P,[1,1],R,[1 1]));
assert_checkequal(t,[1 1]);

P=[1 2 3; 4 5 6;7,8,9];R=[1 0;0 2];
T=lft(P,[2,2],R);
assert_checkalmostequal (T ,-1);
assert_checktrue(T==lft(P,[2,2],R,[0 0]));

P=[1 2 3; 4 5 6;7,8,9];R=[1 0 1;0 2 1];
T=lft(P,[1 1],R);
assert_checkalmostequal (T ,[-13/8,-1,0,-3/8;-5/4,-1,0,-3/4;0,0,2,1]);
assert_checktrue(T==lft(P,[1 1],R,[1 2]));

P=[1 2 3; 4 5 6;7,8,9];R=[1 0 1;0 2 1];
[T,t]=lft(P,[2 1],R);
assert_checkalmostequal (T ,[-7/5,-1,-3/5;-2/5,-2,-13/5]);
assert_checkequal(t,[1 1]);

[T,t]=lft(P,[1 2],R);
assert_checkalmostequal (T ,[-1,6/7,1/7;-1,-6/7,-8/7]);
assert_checkequal(t,[0 0]);


T=lft(R,[2,2],P);
assert_checkalmostequal (T ,[4/3 -5]);

T=lft(R,[2,3],P,[0 1]);
assert_checkequal (T ,[]);


// with transfer functions
s=%s;
P=[1/s 2;3 4];R=2;
T=lft(P,R);
T_ref=(7-12*s)/(7*s);
assert_checkalmostequal (coeff((T-T_ref).num),0);
assert_checktrue(T==lft(P,[1 1],R));

P=[1 2;3 4];R=2/s;
T=lft(P,R);
T_ref=(4+s)/(-8+s);
assert_checkalmostequal (coeff((T-T_ref).num),0);
assert_checktrue(T==lft(P,[1 1],R));

P=[1 2;3/(s+1) 4];R=2/s;
T=lft(P,R);
T_ref=(4-7*s+s^2)/(-8-7*s+s^2);
assert_checkalmostequal (coeff((T-T_ref).num),0);
assert_checktrue(T==lft(P,[1 1],R));


P=[1 2 3; 4 5 6;7/s,8,9];R=[1 0;0 2];
T=lft(P,R);
T_ref=-1;
assert_checkalmostequal (coeff((T-T_ref).num),0,1e-10,1e-10);
assert_checktrue(T==lft(P,[2,2],R));

P=[1 2 3; 4 5 6;7,8,9];R=[1 0;0 2]/s;
T=lft(P,R);
T_ref=(27*s+s^2)/(-6-23*s+s^2);
assert_checkalmostequal (coeff((T-T_ref).num),0,1e-10,1e-10);
assert_checktrue(T==lft(P,[2,2],R));

P=[1 2 3; 4 5 6;7,8,9]/(s-1);R=[1 0;0 2]/s;
T=lft(P,R);
T_ref=(27*s-s^2+s^3)/(-6+23*s-22*s^2-2*s^3+s^4);
assert_checkalmostequal (coeff((T-T_ref).num),[0 0 0],1e-10,1e-10);
assert_checktrue(T==lft(P,[2,2],R));

P=[1 2 3; 4 5 6]/(s-1);R=[1 0;0 2]/s;
T=lft(P,R);
assert_checkequal (T ,[]);

P=[1 2 3; 4 5 6;7/s,8,9];R=[1 0;0 2];
T=lft(P,[2,2],R);
T_ref=-1;
assert_checkalmostequal (coeff((T-T_ref).num),0,1e-10,1e-10);


// with state space

s=%s;
P=tf2ss([1/s 2;3 4]);R=2;
T=lft(P,R);
T_ref=(7-12*s)/(7*s);
assert_checkalmostequal (coeff((ss2tf(T)-T_ref).num),0);
assert_checktrue(T==lft(P,[1,1],R));

P=[1 2;3 4];R=tf2ss(2/s);
T=lft(P,R);
T_ref=(4+s)/(-8+s);
assert_checkalmostequal (coeff((ss2tf(T)-T_ref).num),0);
assert_checktrue(T==lft(P,[1,1],R));

P=tf2ss([1 2;3/(s+1) 4]);R=tf2ss(2/s);
T=lft(P,R);
T_ref=(4-7*s+s^2)/(-8-7*s+s^2);
assert_checktrue (norm(coeff((ss2tf(T)-T_ref).num))<1e-10);


P=tf2ss([1 2 3; 4 5 6;7,8,9]/(s-1));R=tf2ss([1 0;0 2]/s);
T=lft(P,R);
T_ref=(27*s-s^2+s^3)/(-6+23*s-22*s^2-2*s^3+s^4);
assert_checktrue (norm(coeff((ss2tf(T)-T_ref).num))<1e-10);
assert_checktrue(T==lft(P,[2,2],R));

P=tf2ss([1 2 3; 4 5 6;7,8,9]/(s-1));R=tf2ss([1 0;0 2]/s);
T=lft(P,[1,1],R);
T_ref=[12-s+s^2,6-2*s+2*s^2,0*s;6-4*s+4*s^2,3-5*s+5*s^2,0;0,0,2]./[9-8*s-2*s^2+s^3,9-8*s-2*s^2+s^3,1;9-8*s-2*s^2+s^3,9-8*s-2*s^2+s^3,1;1,1,s];

P=tf2ss([1 2 3; 4 5 6]/(s-1));R=tf2ss([1 0;0 2]/s);
T=lft(P,R);
assert_checkequal (T.C ,[]);
assert_checkequal (size(T.A) ,[4,4]);
