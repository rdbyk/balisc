// Copyright (C) 2010 - 2011 - DIGITEO - Michael Baudin
// Copyright (C) 2012 - DIGITEO - Allan CORNET
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [flag,errmsg] = assert_checkerror ( varargin )
    function argin = assert_argindefault ( rhs , vararglist , ivar , default )
        // Returns the value of the input argument #ivar.
        // If this argument was not provided, or was equal to the
        // empty matrix, returns the default value.
        if ( rhs < ivar ) then
            argin = default
        else
            if ( vararglist(ivar) <> [] ) then
                argin = vararglist(ivar)
            else
                argin = default
            end
        end
    endfunction

    //  Check that an instruction produces the expected error.
    if ( nargin < 2 ) then
        error(_("%s: Wrong number of input argument: At least %d expected."), "assert_checkerror", 2)
    end
    //
    // Get arguments
    instr = varargin(1);
    expectedmsg = varargin(2);
    expectederrnb = assert_argindefault ( nargin , varargin , 3 , [] );
    //
    // Check types of variables
    if ( typeof(instr) <> "string" ) then
        error(_("%s: Wrong type for input argument #%d: Matrix of strings expected."), "assert_checkerror", 1)
    end
    if (expectedmsg<>[]) then
        if ( typeof(expectedmsg) <> "string" ) then
            error(_("%s: Wrong type for input argument #%d: Matrix of strings expected."), "assert_checkerror", 2)
        end
    end
    if ( typeof(expectederrnb) <> "constant" ) then
        error(_("%s: Wrong type for input argument #%d: Matrix expected."), "assert_checkerror", 3)
    end
    //
    // Check sizes of variables
    if ( size(instr,"*") <> 1 ) then
        error(_("%s: Wrong size for input argument #%d: %d-by-%d matrix expected."), "assert_checkerror", 1, 1, 1)
        error(errmsg)
    end
    if (expectedmsg<>[]) then
        if ((size(expectedmsg, "r") > 1) & (size(expectedmsg, "c") > 1))
            error(_("%s: Wrong size for input argument #%d: A string vector expected."), "assert_checkerror", 2);
        end
    end
    if ( expectederrnb <> [] ) then
        if ( size(expectederrnb,"*") <> 1 ) then
            error(_("%s: Wrong size for input argument #%d: %d-by-%d matrix expected."), "assert_checkerror", 3, 1, 1)
        end
    end
    //
    // Check values of variables
    if (expectedmsg<>[]) then
        if ( expectederrnb <> [] ) then
            if ( expectederrnb < 0 ) then
                error(_("%s: Wrong value for input argument #%d: Non-negative integers expected."), "assert_checkerror", 3)
            end
        end
    else
        // If the message is empty (arg #2), check that the error
        // number is not empty (arg #3).
        if ( expectederrnb == [] ) then
            error(_("%s: Wrong size for input argument #%d: Non-empty matrix expected."), "assert_checkerror", 3)
        end
    end
    //
    // Proceed...
    compierr = execstr(instr,"errcatch")
    //
    // Check that an error is produced
    if ( compierr == 0 ) then
        error(_("%s: No error was produced while evaluating ""%s""."), "assert_checkerror", instr)
    end
    //
    // Get the error
    compmsg = lasterror();
    //
    // Initialize output arguments
    flag = %t
    errmsg = ""
    //
    // Localize the message, if necessary.
    if ( nargin >= 4 ) then
        localmsg = gettext(expectedmsg)
        instr = "expectedmsg = msprintf(localmsg, varargin(4:$))"
        ierr = execstr(instr,"errcatch")
        if ( ierr <> 0 ) then
            fmterrmsg = lasterror();
            localstr = gettext ( "%s: Error while formatting the error message: ""%s""")
            error(_("%s: Error while formatting the error message: ""%s"""), "assert_checkerror", fmterrmsg)
        end
    end
    //
    // Check the error message
    if (expectedmsg <> []) then
        isdifferentmsg = or(expectedmsg <> compmsg);

        if (isdifferentmsg) then
            flag = %f
            if size(compmsg, "*") <> 1 then
                compmsg = sci2exp(compmsg);
            end
            if size(expectedmsg, "*") <> 1 then
                expectedmsg = sci2exp(expectedmsg);
            end
            if ( nargout < 2 ) then
                // If no output variable is given, generate an error
                error(_("%s: Assertion failed: expected error message = ""%s"" while computed error message = ""%s""."), "assert_checkerror", expectedmsg, compmsg)
            else
                return
            end
        end
    end
    if ( expectederrnb <> [] ) then
        //
        // Check the error number
        if ( expectederrnb <> compierr ) then
            flag = %f
            if ( nargout < 2 ) then
                // If no output variable is given, generate an error
                error(_("%s: Assertion failed: expected error number = %d while computed error number = %d."), "assert_checkerror", expectederrnb, compierr)
            else
                return
            end
        end
    end
endfunction
