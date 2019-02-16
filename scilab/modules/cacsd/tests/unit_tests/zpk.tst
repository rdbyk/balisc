//<-- CLI SHELL MODE -->
// This file is part of the zpk module
// Copyright (C) 2016 - Serge Steer - INRIA
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// For more information, see the COPYING file which you should have received
// along with this program.

// Tests of zpk function
//----------------------------------------------------------------
z11=[1 -0.5];p11=[-2 -3+2*%i -3-2*%i  ];k11=1;
S11=zpk(z11,p11,k11,"c");


assert_checkequal(S11.Z{1},z11.');
assert_checkequal(S11.P{1},p11.');
assert_checkequal(S11.K,k11);

z21=0.3;p21=[-3+2*%i -3-2*%i];k21=1.5;
S21=zpk(z21,p21,k21,"c");
S12=zpk([],0,1,"c");
S22=zpk(1,-3,1,"c");
S=zpk({z11 [];z21 1},{p11,0;p21 -3},[k11 1;k21 1],"c");
assert_checkequal(S.Z{1,1},z11.');
assert_checkequal(S.P{1,1},p11.');
assert_checkequal(S.K(1,1),k11);
assert_checkequal(S.Z{1,2},[]);
assert_checkequal(S.P{1,2},0);
assert_checkequal(S.K(1,2),1);
assert_checkequal(S.Z{2,1},z21.');
assert_checkequal(S.P{2,1},p21.');
assert_checkequal(S.K(2,1),k21);
assert_checkequal(S.Z{2,2},1);
assert_checkequal(S.P{2,2},-3);
assert_checkequal(S.K(2,2),1);

h1=syslin("c",5*(%s-1)*(%s-3)/(%s^2-4));
Sh1=zpk(h1);
assert_checkalmostequal(Sh1.Z{1},[3;1]);
assert_checkalmostequal(Sh1.P{1},[2;-2]);
assert_checkalmostequal(Sh1.K,5);
Ss1=zpk(tf2ss(h1));
assert_checkalmostequal(Ss1.Z{1},[3;1]);
assert_checkalmostequal(Ss1.P{1},[2;-2]);
assert_checkalmostequal(Ss1.K,5);


h2=syslin("c",1/(%s^2+1));
Sh=zpk([h1 h2]);
assert_checkalmostequal(Sh.Z{1,1},[3;1]);
assert_checkalmostequal(Sh.P{1,1},[2;-2]);
assert_checkalmostequal(Sh.K(1,1),5);
assert_checkalmostequal(Sh.Z{1,2},[]);
assert_checkalmostequal(Sh.P{1,2},[%i;-%i]);
assert_checkalmostequal(Sh.K(1,2),1);
Ss=zpk(tf2ss([h1 h2]));
assert_checkalmostequal(Ss.Z{1,1},[3;1]);
assert_checkalmostequal(Ss.P{1,1},[2;-2]);
assert_checkalmostequal(Ss.K(1,1),5);
assert_checkalmostequal(Ss.Z{1,2},[]);
assert_checkalmostequal(Ss.P{1,2},[%i;-%i]);
assert_checkalmostequal(Ss.K(1,2),1);
// test of function size
//----------------------------------------------------------------
assert_checkequal(size(S11),[1 1]);
assert_checkequal(size(S11,1),1);
assert_checkequal(size(S,2),2);
assert_checkequal(size(S,"*"),4);
assert_checkequal(size(S,"r"),2);

// Tests of comparisons
//----------------------------------------------------------------
assert_checkequal(S11==S11,%t);
assert_checkequal(S==S,[%t %t;%t %t]);
assert_checkequal(S==S11,[%t %f;%f %f]);
assert_checkequal(S<>S11,[%f %t;%t %t]);
assert_checkequal(S11<>S11,%f);

//test of references and catenation
//----------------------------------------------------------------
assert_checktrue(S(1)==S11);
assert_checktrue(S(1,1)==S11);
assert_checktrue(S(:,1)==[S11;S21]);
assert_checktrue(S(1,:)==[S11, S12]);

assert_checktrue([S11 []]==S11);
assert_checktrue([[] S11]==S11);
assert_checktrue([S11;[]]==S11);
assert_checktrue([[];S11]==S11);

tmp=[S11 1];
assert_checktrue(tmp(1,1)==S11);
assert_checktrue(tmp(1,2)==zpk([],[],1,"c"));

tmp=[1 S11];
assert_checktrue(tmp(1,2)==S11);
assert_checktrue(tmp(1,1)==zpk([],[],1,"c"));

tmp=[S11;1];
assert_checktrue(tmp(1,1)==S11);
assert_checktrue(tmp(2,1)==zpk([],[],1,"c"));
tmp=[1;S11];
assert_checktrue(tmp(2,1)==S11);
assert_checktrue(tmp(1,1)==zpk([],[],1,"c"));

tmp=[S [5;7]];
assert_checktrue(tmp(:,1:2)==S);
assert_checktrue(tmp(:,$)==zpk({[];[]},{[];[]},[5;7],"c"));
tmp=[[5;7] S];
assert_checktrue(tmp(:,2:$)==S);
assert_checktrue(tmp(:,1)==zpk({[];[]},{[];[]},[5;7],"c"));

assert_checktrue([S11 h1]==[S11 zpk(h1)]);
assert_checktrue([h1;S11]==[zpk(h1);S11]);
assert_checktrue([S;Sh]==[S;zpk(Sh)]);
assert_checktrue([Sh;S]==[zpk(Sh);S]);

// Tests of assignments
//----------------------------------------------------------------
tmp=S;
tmp(1,1)=S12;
assert_checktrue(tmp==[S12 S12;S21 S22]);
tmp(:,1)=[S12;S12];
assert_checktrue(tmp==[S12 S12;S12 S22]);

// Tests of transpose
//----------------------------------------------------------------
assert_checktrue([S11 S12]'==[S11;S12]);
assert_checktrue(S'==[S11 S21;S12 S22]);

// Test of sum, + and -
//----------------------------------------------------------------
z11=[1 -0.5];p11=[-2 -3+2*%i -3-2*%i  ];k11=1;
S11=zpk(z11,p11,k11,"c");
z21=0.3;p21=[-3+2*%i -3-2*%i];k21=1.5;
S21=zpk(z21,p21,k21,"c");
S12=zpk([],0,1,"c");
S22=zpk(1,-3,1,"c");
S=zpk({z11 [];z21 1},{p11,0;p21 -3},[k11 1;k21 1],"c");
h1=syslin("c",1/(1-%s));
Sh1=tf2ss(h1);

s=S11+S12;
Z=[-1.1452362725849+%i*2.7559801007529;
-1.1452362725849-%i*2.7559801007529;
-1.4595274548302];
P=[0;-2;-3+%i*2;-3-%i*2];
K=2;
assert_checkalmostequal(s.Z{1},Z);
assert_checktrue(s.P{1}==P);
assert_checktrue(s.K==K);
s=S+S;
assert_checktrue(s.Z{1}==S.Z{1});
assert_checktrue(s.P{1}==S.P{1});
assert_checktrue(s.K==2*S.K);

s=-S;
assert_checktrue(s.Z{1}==S.Z{1});
assert_checktrue(s.P{1}==S.P{1});
assert_checktrue(s.K==-S.K);

assert_checktrue(S11-S12==S11+(-S12));
assert_checktrue(S-S==zpk(cell(2,2),cell(2,2),zeros(2,2),"c"));

s=S22+S12;
Z=[%i;-%i]*sqrt(3);
P=[0;-3];
K=1;
assert_checkalmostequal(s.Z{1},Z);
assert_checktrue(s.P{1}==P);
assert_checktrue(s.K==K);

s=S22-S12;
Z=[3;-1];
P=[0;-3];
K=1;
assert_checkalmostequal(s.Z{1},Z);
assert_checktrue(s.P{1}==P);
assert_checktrue(s.K==K);


assert_checktrue(S12+1==zpk(-1,0,1,"c"));
assert_checktrue(1+S12==zpk(-1,0,1,"c"));

assert_checktrue(h1+S12==zpk([],[0 1],-1,"c"));
assert_checktrue(S12+h1==zpk([],[0 1],-1,"c"));
assert_checktrue(h1-S12==zpk(0.5,[0 1],-2,"c"));
assert_checktrue(S12-h1==zpk(0.5,[0 1],2,"c"));

s=S12-Sh1;
assert_checktrue(s.A==[0 0;0 1]);
assert_checktrue(s.B==[1;-1]);
assert_checktrue(s.C==[1 -1]);
assert_checktrue(s.D==0);
s=Sh1-S12;
assert_checktrue(s.A==[1 0;0 0]);
assert_checktrue(s.B==[1;-1]);
assert_checktrue(s.C==[-1 1]);
assert_checktrue(s.D==0);

// Test of *
//----------------------------------------------------------------
z11=[1 -0.5];p11=[-2 -3+2*%i -3-2*%i  ];k11=1;
S11=zpk(z11,p11,k11,"c");
z21=0.3;p21=[-3+2*%i -3-2*%i];k21=1.5;
S21=zpk(z21,p21,k21,"c");
S12=zpk([],0,1,"c");
S22=zpk(1,-3,1,"c");
S=zpk({z11 [];z21 1},{p11,0;p21 -3},[k11 1;k21 1],"c");


// "scalar"*"scalar"
assert_checktrue(S12*S12==zpk([],[0 0],1,"c"));
assert_checktrue(S11*S11==zpk([z11 z11],[p11 p11],k11^2,"c"));

// "scalar"*matrix and matrix*"scalar"
S2=S*S12;
assert_checktrue(S2(1,1)==S(1,1)*S12);
assert_checktrue(S2(2,1)==S(2,1)*S12);
assert_checktrue(S2(1,2)==S(1,2)*S12);
assert_checktrue(S2(2,2)==S(2,2)*S12);
S2=S12*S;
assert_checktrue(S2(1,1)==S(1,1)*S12);
assert_checktrue(S2(2,1)==S(2,1)*S12);
assert_checktrue(S2(1,2)==S(1,2)*S12);
assert_checktrue(S2(2,2)==S(2,2)*S12);

//matrix*matrix
S2=S(1,:)*S(:,1);
Z=[0.2992047956058;
-1.4216535670946+%i*0.5022286865922;
-1.4216535670946-%i*0.5022286865922;
-1.4379488307083+%i*3.4195209906928;
-1.4379488307083-%i*3.4195209906928];
P=[0;-2;-2;-3+%i*2;-3+%i*2;-3-%i*2;-3-%i*2];
K=2.5;
assert_checkalmostequal(S2.Z{1},Z);
assert_checktrue(S2.P{1}==P);
assert_checkalmostequal(S2.K,K);
assert_checktrue((S*S)(1,1)==S2);
S2=S(2,:)*S(:,1);
Z=[1;
0.3;
-1.7226779397091;
-3.6386610301454+%i*1.6503526090746;
-3.6386610301454-%i*1.6503526090746];
P=[-2;-3+%i*2;-3+%i*2;-3;-3-%i*2;-3-%i*2];
K=1.5;
assert_checkalmostequal(S2.Z{1},Z);
assert_checktrue(S2.P{1}==P);
assert_checkalmostequal(S2.K,K);
assert_checktrue((S*S)(2,1)==S2);
//mixed type products
h1=syslin("c",5*(%s-1)*(%s-3)/(%s^2-4));
h2=syslin("c",1/(%s^2+1));

S2=S11*2;
assert_checktrue(S2.Z==S11.Z&S2.P==S11.P&S2.K==2*S11.K);
S2=3*S11;
assert_checktrue(S2.Z==S11.Z&S2.P==S11.P&S2.K==3*S11.K);


S2=eye(2,2)*S;
for i=1:2,
    for j=1:2
        assert_checkalmostequal(S2.Z{i,j},S.Z{i,j});
    end;
end
assert_checktrue(S2.P==S.P);
assert_checkalmostequal(S2.K,S.K);

S2=S*eye(2,2);
for i=1:2,
    for j=1:2
        assert_checkalmostequal(S2.Z{i,j},S.Z{i,j});
    end;
end
assert_checktrue(S2.P==S.P);
assert_checkalmostequal(S2.K,S.K);

assert_checktrue(S11*h1==S11*zpk(h1));
assert_checktrue(h1*S11==zpk(h1)*S11);
assert_checktrue(S(1,:)*[h1;h2]==S(1,:)*zpk([h1;h2]));
assert_checktrue([h1;h2]*S(1,:)==zpk([h1;h2])*S(1,:));

s1=tf2ss(h1);
s2=tf2ss(h2);
assert_checktrue(S(2,:)*[s1;s2]==zpk2ss(S(2,:))*[s1;s2]);
assert_checktrue([s1 s2]*S(:,2)==[s1 s2]*zpk2ss(S(:,2)));


// Test of .*
//----------------------------------------------------------------
z11=[1 -0.5];p11=[-2 -3+2*%i -3-2*%i  ];k11=1;
S11=zpk(z11,p11,k11,"c");
z21=0.3;p21=[-3+2*%i -3-2*%i];k21=1.5;
S21=zpk(z21,p21,k21,"c");
S12=zpk([],0,1,"c");
S22=zpk(1,-3,1,"c");
S=zpk({z11 [];z21 1},{p11,0;p21 -3},[k11 1;k21 1],"c");
h1=syslin("c",5*(%s-1)*(%s-3)/(%s^2-4));
h2=syslin("c",1/(%s^2+1));

assert_checktrue(S11.*S21==zpk([z11 z21],[p11 p21],k11*k21,"c"));
assert_checktrue(S.*S11==S*S11);
assert_checktrue(S11.*S==S*S11);

Z=cell(2,2);P=cell(2,2);
for i=1:2
    for j=1:2
        Z{i,j}=[S.Z{i,j};S.Z{i,j}];
        P{i,j}=[S.P{i,j};S.P{i,j}];
    end
end
assert_checktrue(S.*S==zpk(Z,P,S.K.*S.K,"c"));

A=[1 2;3 4];
assert_checktrue(S.*A==zpk(S.Z,S.P,S.K.*A,"c"));
assert_checktrue(A.*S==zpk(S.Z,S.P,S.K.*A,"c"));

A=5;
assert_checktrue(S.*A==zpk(S.Z,S.P,S.K.*A,"c"));
assert_checktrue(A.*S==zpk(S.Z,S.P,S.K.*A,"c"));

assert_checktrue(S.*h1==S.*zpk(h1));
assert_checktrue(h1.*S==S.*zpk(h1));
assert_checktrue([h1 h2].*S(1,:)==zpk([h1 h2]).*S(1,:));

if %f then
    //skip because %lss_x_lss not implemented
    s1=tf2ss(h1);s2=tf2ss(h2);
    assert_checktrue(S.*s1==S.*zpk(s1));
    assert_checktrue(s1.*S==S.*zpk(s1));
    assert_checktrue([s1 s2].*S(1,:)==zpk([s1 s2]).*S(1,:));
end


//test of / and \
z11=[1 -0.5];p11=[-2 -3+2*%i -3-2*%i  ];k11=1;
S11=zpk(z11,p11,k11,"c");
z21=0.3;p21=[-3+2*%i -3-2*%i];k21=1.5;
S21=zpk(z21,p21,k21,"c");
S12=zpk([],0,1,"c");
S22=zpk(1,-3,1,"c");
S=zpk({z11 [];z21 1},{p11,0;p21 -3},[k11 1;k21 1],"c");
h1=syslin("c",1/(1-%s));
Sh1=tf2ss(h1);

assert_checktrue(S11/S12==zpk([0 1 -0.5],p11,1,"c"));
assert_checktrue(S12\S11==zpk([0 1 -0.5],p11,1,"c"));

assert_checktrue(S/S12==S*zpk(0,[],1,"c"));
assert_checktrue(S12\S==S*zpk(0,[],1,"c"));

s1=S;s1.K=s1.K/2;
assert_checktrue(S/2==s1);
assert_checktrue(2\S==s1);

assert_checktrue(S/h1==S*zpk(1,[],-1,"c"));
assert_checktrue(h1\S==S*zpk(1,[],-1,"c"));
assert_checktrue(S/Sh1==S*zpk(1,[],-1,"c"));
assert_checktrue(Sh1\S==S*zpk(1,[],-1,"c"));

s1=minss(S/S);
assert_checktrue(s1.A==[]&s1.B==[]&s1.C==[]);
assert_checkalmostequal(clean(s1.D),eye(2,2)+0*%s,1e-10,1e-10);
s1=minss(S\S);
assert_checktrue(s1.A==[]&s1.B==[]&s1.C==[]);
assert_checkalmostequal(s1.D,eye(2,2),1e-10,1e-10);

//test of ./ and .\
assert_checktrue(S11./S12==zpk([0 1 -0.5],p11,1,"c"));
assert_checktrue(S12.\S11==zpk([0 1 -0.5],p11,1,"c"));

assert_checktrue(S./S12==S*zpk(0,[],1,"c"));
assert_checktrue(S12.\S==S*zpk(0,[],1,"c"));

s1=S;s1.K=s1.K/2;
assert_checktrue(S./2==s1);
assert_checktrue(2 .\S==s1);

assert_checktrue(S./h1==S*zpk(1,[],-1,"c"));
assert_checktrue(h1.\S==S*zpk(1,[],-1,"c"));
assert_checktrue(S./Sh1==S*zpk(1,[],-1,"c"));
assert_checktrue(Sh1.\S==S*zpk(1,[],-1,"c"));

assert_checktrue(S./S==zpk({[],[];[],[]},{[],[];[],[]},ones(2,2),"c"));
assert_checktrue(S.\S==zpk({[],[];[],[]},{[],[];[],[]},ones(2,2),"c"));

s1=S./[1 2;4 1];
assert_checktrue(s1.Z==S.Z&s1.P==S.P&s1.K==S.K./[1 2;4 1]);
