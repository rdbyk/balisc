// Copyright (C) 2008-2009 - INRIA - Michael Baudin
// Copyright (C) 2010 - 2011 - DIGITEO - Michael Baudin
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2019 - 2020 - Samuel GOUGEON
// Copyright (C) 2018 - 2020 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [flag, errmsg] = assert_checkequal(computed, expected)
    //  Check that computed and expected are equal.

    if ( nargin <> 2 ) then
        error(71, 2);
    end

    // Check types of variables
    if ( typeof(computed) <> typeof(expected) ) then
        errmsg = gettext("%s: Incompatible input arguments #%d and #%d: Same types expected.\n")
        error(msprintf(errmsg, "assert_checkequal", 1, 2))
    end

    // Check sizes of variables
    if type(computed)==15 then
        ncom = length(computed)
        nexp = length(expected)
    elseif or(typeof(computed)==["ce" "st"])
        ncom = size(computed)
        nexp = size(expected)
    else
        try
            ncom = size(computed)
            nexp = size(expected)
        catch   // non-sizeable objects: 1:$, iolib, sin, sind, etc
            ncom = -2
            nexp = -2
        end
    end
    if ( or(ncom <> nexp) ) then
        errmsg = msprintf(gettext ( "%s: Incompatible input arguments #%d and #%d: Same sizes expected.\n"), "assert_checkequal", 1 , 2)
        error(errmsg)
    end
    //
    if ( type(computed) == 1 & type(expected) == 1 ) then
        // These are two matrices of doubles
        cisreal = isreal(computed)
        eisreal = isreal(expected)
        if ( cisreal & ~eisreal ) then
            errmsg = msprintf(gettext("%s: Computed is real, but expected is complex."), "assert_checkequal")
            error(errmsg)
        end
        if ( ~cisreal & eisreal ) then
            errmsg = msprintf(gettext("%s: Computed is complex, but expected is real."), "assert_checkequal")
            error(errmsg)
        end
        if ( cisreal & eisreal ) then
            flag = comparedoubles ( computed , expected )
        else
            [flag, k] = comparedoubles ( real(computed) , real(expected) )
            if flag then
                [flag ,k] = comparedoubles ( imag(computed) , imag(expected) )
            end
        end
        // k is the index of the first discrepancy (or [] if none)

    elseif or(typeof(computed)==["implicitlist" "fptr" "function"])
                                    // http://bugzilla.scilab.org/16104 C) D) E)
        flag = computed==expected
        if ~flag then
            if typeof(computed) == "implicitlist"
                errmsg = _("%s: Assertion failed: expected= %s  while computed= %s")
                errmsg = msprintf(errmsg,"assert_checkequal",string(expected),string(computed))

            elseif typeof(computed) == "function"
                c = macr2tree(computed).name+"()"
                e = macr2tree(expected).name+"()"
                errmsg = _("%s: Assertion failed: expected= %s  while computed= %s")
                errmsg = msprintf(errmsg,"assert_checkequal", e, c)

            else
                flag = %f
            end
        end
        return

    elseif type(computed) == 14   // library : http://bugzilla.scilab.org/16104#c1
        flag = and(string(computed)==string(expected))
        if ~flag then
            errmsg = gettext("%s: Assertion failed: expected= %s  while computed= %s")
            c = "lib@" + string(computed)(1)
            e = "lib@" + string(expected)(1)
            errmsg = msprintf(errmsg,"assert_checkequal", e, c)
            if lhs < 2 then
                assert_generror ( errmsg )
            end
        end
        return

    elseif or(type(computed)==[15 16 17 ])
        [flag, k] = compareContainers(computed , expected)

    elseif type(computed) == 0
        flag = %t
        
    else
        if ( and ( computed == expected ) ) then
            flag = %t
        else
            flag = %f
        end
    end

    if ( flag == %t ) then

        errmsg = ""
    else
        // Sets the message according to the type and size of the pair:
        if or(typeof(expected) == ["sparse", "boolean sparse"])
            estr = string(full(expected(k)))
        else
            s = "expected(1)"
            if isdef("k","l") & k <> []
                s = "expected(k)"
            end
            err = execstr("e = "+s+"; t = type("+s+")", "errcatch")
            if err <> 0
                e = expected
                t = type(e)
            end
            if t==0
                estr = "(void)"
            elseif t==9
                estr = msprintf("%s(uid:%d)", e.type, e.uid)
            else
                estr = string(e)
            end
        end
        //
        if or(typeof(computed) == ["sparse", "boolean sparse"])
            cstr = full(computed(k))
        else
            s = "computed(1)"
            if isdef("k","l") & k <> []
                s = "computed(k)"
            end
            err = execstr("c = "+s+"; t = type("+s+")", "errcatch")
            if err <> 0
                c = computed
                t = type(c)
            end
            if t==0
                cstr = "(void)"
            elseif t==9
                cstr = msprintf("%s(uid:%d)", c.type, c.uid)
            else
                cstr = string(c)
            end
        end
        //
        if isdef("k","l") & k <> [] & length(computed)>1
            estr = msprintf(_("expected(%d)= "),k) + estr
            cstr = msprintf(_("computed(%d)= "),k) + cstr
        else
            if ( or(typeof(computed) == ["sparse", "boolean sparse"])) then
                val = full(computed(1))
            else
                val = computed(1)
            end
            cstr = "[" + string(val) + " ...]"
        end
        ierr = execstr("mdiff = string(mean(computed - expected))", "errcatch");
        if ( ierr == 0 ) then
            errmsg = msprintf(gettext("%s: Assertion failed: expected = %s while computed = %s (mean diff = %s)"),"assert_checkequal",estr,cstr,mdiff)
        else
            errmsg = msprintf(gettext("%s: Assertion failed: expected = %s while computed = %s"),"assert_checkequal",estr,cstr)
        end
        if ( nargout < 2 ) then
            // If no output variable is given, generate an error
            assert_generror ( errmsg )
        end
    end
endfunction
// ---------------------------------------------------------------------------
function [flag, k] = comparedoubles ( computed , expected )
    rand("seed",getdate("s"))
    joker = rand(1);
    while find(expected==joker | computed==joker,1)<>[]
        joker = rand(1);
    end
    computed(isnan(computed)) = joker;
    expected(isnan(expected)) = joker;
    k = find(expected<>computed,1);
    flag = k==[];
endfunction
// ---------------------------------------------------------------------------
function [areEqual, k] = compareContainers(computed , expected)
    // http://bugzilla.scilab.org/15293
    // http://bugzilla.scilab.org/16274
    tc = typeof(computed)
    te = typeof(expected)
    k = []
    areEqual = tc == te
    if ~areEqual
        return
    end
    if or(type(computed)==[1 5])
        if and(computed == expected)
            return
        end
        if isreal(computed) <> isreal(expected)
            areEqual = %f
            return
        end
        [areEqual, k] = comparedoubles(real(computed), real(expected))
        if areEqual
            [areEqual, k] = comparedoubles(imag(computed), imag(expected))
        end

    elseif or(type(computed)==[16 17]) then
        if and(computed == expected)
            return
        end
        if or(size(computed) <> size(expected)) then
            areEqual = %f
            return
        end
        fc = fieldnames(computed)
        areEqual = and(fc == fieldnames(expected))
        if ~areEqual
            return
        end
        if fc <> []
            for f = fc'
                [areEqual, k] = compareContainers(computed(f) , expected(f))
                if ~areEqual
                    break
                end
            end
        elseif tc=="ce"
            [areEqual, k] = compareContainers(computed{:} , expected{:})
            if ~areEqual
                break
            end
        end

    elseif type(computed)==14   // Libraries
        areEqual = and(string(computed)==string(expected))

    elseif tc=="list"
        if and(computed == expected)
            return
        end
        if length(computed) <> length(expected)
            areEqual = %f
            return
        end
        dfc = definedfields(computed)
        dfe = definedfields(expected)
        if or(dfc <> dfe)
            if length(dfc)==length(dfe)
                k = find(dfc <> dfe, 1)
            else
                tmp = union(setdiff(dfc, dfe), setdiff(dfe, dfc))
                k = tmp(find(tmp,1))
            end
            areEqual = %f
            return
        end
        for k = dfc
            areEqual = compareContainers(computed(k) , expected(k))
            if ~areEqual
                break
            end
        end

    elseif (tc=="void" & te=="void")
        return

    elseif type(computed) <> 0
        b = and(computed == expected)
        areEqual = b || isequal(computed, expected)
        if ~areEqual & ~b
            k = find(computed <> expected, 1);
        end
    end
endfunction
