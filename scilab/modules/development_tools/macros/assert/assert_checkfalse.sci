// Copyright (C) 2008-2009 - INRIA - Michael Baudin
// Copyright (C) 2010 - 2011 - DIGITEO - Michael Baudin
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - 2021 Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function [flag,errmsg] = assert_checkfalse ( condition )
    //   Check that condition is false. All its components must be False.

    if ( nargin <> 1 ) then
        error(71, 1)
    end
    //
    // Check types of variables
    if and(typeof(condition) <> ["boolean" "boolean sparse"]) then
        errmsg = gettext("%s: Wrong type for input argument #%d: Boolean matrix expected.\n")
        errmsg = msprintf(errmsg, "assert_checkfalse", 1)
        error(errmsg)
    end
    //
    if ( and(~condition) ) then
        flag = %t
        errmsg = ""
    else
        flag = %f
        k = find(condition, 1);
        errmsg = gettext("%s: Assertion failed: Entry %%T found in condition(%d).\n")
        errmsg = strsubst(msprintf(errmsg, "assert_checkfalse", k), "%T", "%%T")
        if ( nargout < 2 ) then
            // If no output variable is given, generate an error
            assert_generror ( errmsg )
        end
    end
endfunction
