// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2000 - 2016 - INRIA - Serge Steer
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - 2020 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function plzr(a,b,c,d)

    if nargin == 0 then
        s=poly(0,"s");
        n=[1+s, 2+3*s+4*s^2, 5;0, 1-s, s];
        d=[1+3*s, 5-s^3, s+1;1+s, 1+s+s^2, 3*s-1];
        h=syslin("c",n./d);
        plzr(h);
        return;
    end

    select typeof(a)
    case "rational" then
        if nargin<>1 then
            error(71,1);
        end
        dt=a.dt;
        [a,b,c,d]=abcd(tf2ss(a)),

    case "state-space" then
        if nargin<>1 then
            error(71,1);
        end
        dt=a.dt
        [a,b,c,d]=abcd(a)
    case "constant" then
        if nargin<>4 then
            error(71,4);
        end

        dt=[];
    case "zpk" then
        dt=a.dt;
        [a,b,c,d]=abcd(zpk2ss(a));
    else
        if nargin==1 then
            error(90, 1, gettext("Linear dynamical system"));
        else
            error(90, 1, gettext("Array of floating point numbers"));
        end
    end

    if type(d)<>1 then
        error(90, 4, gettext("Array of floating point numbers"));
    end

    dr=spec(a)
    [al,be]=tr_zer(a,b,c,d)
    nr=al./be
    ni=imag(nr);nr=real(nr)
    di=imag(dr);dr=real(dr)
    //
    mxx=max([nr;dr;1]*1.1)
    mnx=min([nr;dr;-1]*1.1)
    my=max(abs([ni;di;1])*1.1)

    rect=[mnx, -my, mxx, my];

    wdim=get(gcf(),"axes_size")
    dx=(mxx-mnx)/wdim(1);dy=2*my/wdim(2)
    if dy>dx then
        ax=(dy*wdim(1)-mxx+mnx)/2
        mxx=mxx+ax;mnx=mnx-ax
    elseif dy<dx then
        ay=(dx*wdim(2)-2*my)/2
        my=my+ay
    end
    rect=[mnx, -my, mxx, my];

    fig=gcf();
    immediate_drawing=fig.immediate_drawing;
    fig.immediate_drawing="off";

    ax=gca();
    ax.data_bounds=[mnx, -my; mxx, my];
    ax.axes_visible="on";
    ax.clip_state="on";

    legs=[],lhandle=[]
    if size(nr,"*")<>0 then
        xpoly(nr,ni)
        e=gce();e.line_mode="off";e.mark_mode="on";
        e.mark_size_unit="point";e.mark_size=7;e.mark_style=9;
        legs=gettext("Zeros")
        lhandle=[e;lhandle]
    end;
    if size(dr,"*")<>0 then
        xpoly(dr,di)
        e=gce();e.line_mode="off";e.mark_mode="on";
        e.mark_size_unit="point";e.mark_size=7;e.mark_style=2;
        legs=[gettext("Poles");legs]
        lhandle=[e;lhandle]
    end

    ax.grid=ones(1,3)*color("gray")
    ax.box = "on";
    ax.auto_scale="off";

    ax.title.text=gettext("Transmission Zeros and Poles");
    ax.x_label.text=gettext("Real Axis");
    ax.y_label.text=gettext("Imaginary Axis");
    ax.title.font_size=4;
    ax.x_label.font_size=2;
    ax.y_label.font_size=2;

    if dt == "d" | type(dt) == 1 then
        xarc(-1,1,2,2,0,360*64)
        e=gce(); e.foreground=5; e.line_style=8;
    else
        xsegs([0,0], ax.y_ticks.locations([1 $])')
        e=gce(); e.segs_color=5; e.line_style=8;
    end

    if legs<>[] then legend(lhandle,legs,1).marks_count=1,end
    fig.immediate_drawing=immediate_drawing;
    show_window();
endfunction
