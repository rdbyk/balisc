// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) INRIA
// Copyright (C) DIGITEO - 2012 - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function %r_p(h)

    //used to display rational fraction with complex coefficients
    //The real case is hard coded
    if size(size(h),"*")>2 then
        //hypermatrix case
        %hmr_p(h)
        return
    end

    [m, n]=size(h);
    if (m == 0) | (n == 0) then
        return
    end
    del=" "
    blank=" "
    if m*n==1 then del=" ",end
    height=zeros(m,1)  // to store "height" of each row do be displayed
    width=zeros(1,n) // to store "width" of each column do be displayed
    T=list() // to store display of each entry of the rational
    for k=1:n
        for l=1:m
            tlk=r2str(h(l,k))
            height(l)=max(size(tlk,1),height(l))
            width(k)=max(max(length(tlk)),width(k))
            T($+1)=tlk
        end
    end
    ll=lines()
    k0=0

    //manage column display
    while %t
        // find how many columns can be displayed simultaneously
        last=find(cumsum(width+2)<ll(1)-3);last=last($);
        if last==[] then last=1,end
        // form display of these columns
        txt=[]
        for l=1:m
            txtr=emptystr(height(l),1)
            for k=1:last
                txtr=txtr+part(blank(ones(height(l),1)),1:2)
                tlk=T(l+(k0+k-1)*m)
                iPad = (width(k)-max(length(tlk)))/2;
                if iPad>=1
                    tlk=part(blank,1:iPad)+tlk;
                end
                txtr=txtr+[part(tlk,1:width(k));emptystr(height(l)-size(tlk,1),1)]
            end
            txt=[txt;ascii(13);txtr]
        end
        // add matrix delimiter and columns title and display
        nt=size(txt,1)
        txt=part(txt,1:max(length(txt)))

        if k0==0&last==n then
            r = del(ones(nt,1))+txt+blank(ones(nt,1))+del(ones(nt,1));
            for i=1:size(r,"*")
                mprintf("%s\n", r(i))
            end
        else
            if last==1 then
                leg="column "+string(k0+1)
            else
                leg="column "+string(k0+1)+" to "+string(k0+last)
            end

            r = [" "; leg; " ";del(ones(nt,1))+txt+blank(ones(nt,1))+del(ones(nt,1))];
            for i=1:size(r,"*")
                mprintf("%s\n", r(i))
            end
        end
        width(1:last)=[]
        k0=last
        if width==[] then break,end
    end

endfunction

function txt=r2str(h)
    //form display of a single rational with complex coefficients
    dash=ascii([226 148 128]);
    blank=" "

    t1=string(h("num")) //display of numerator
    t2=string(h("den")) //display of denominator

    //add fraction bar and center
    l1=max(length(t1))
    l2=max(length(t2))
    if l1>l2 then
        ll1=int((l1-l2)/2)
        ll2=l1-l2-ll1
        b=blank(ones(size(t2,"*"),1))
        txt=[t1;
        part(dash,ones(1,l1));
        part(b,ones(1,ll1))+t2+part(b,ones(1,ll2))]
    elseif l1<l2 then
        ll1=int((l2-l1)/2)
        ll2=l2-l1-ll1
        b=blank(ones(size(t1,"*"),1))
        txt=[part(b,ones(1,ll1))+t1+part(b,ones(1,ll2));
        part(dash,ones(1,l2));
        t2]
    else
        txt=[t1;part(dash,ones(1,l1));t2]
    end
endfunction

function   %hmr_p(h)
    // hypermatrix display
    dims=size(h)
    num=h.num
    den=h.den
    nd=size(dims,"*")
    I=(1:dims(3));
    for k=4:nd
        I=[ones(1,dims(k)).*.I;
        (1:dims(k)).*.ones(1,size(I,2))];
    end
    k=1;sz=dims(1)*dims(2)
    for II=I
        tit="(:,:,"+strcat(string(II'),",")+")"
        mprintf("%s\n",tit)
        hb=rlist(matrix(num(k:k-1+sz),dims(1),dims(2)),matrix(den(k:k-1+sz),dims(1),dims(2)),h.dt)
        %r_p(hb)
        k=k+sz
    end
endfunction
