// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2002-2004 - INRIA - Vincent COUVERT
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2019 - Samuel GOUGEON
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

function tree = sci_atan(tree)
    // File generated from sci_PROTO5.g: PLEASE DO NOT EDIT !
    // M2SCI function
    // Conversion function for Matlab atan()
    // Input: tree = Matlab funcall tree
    // Output: tree = Scilab equivalent for tree

    A = getrhs(tree)
    A = convert2double(A)
    tree.rhs = Rhs_tlist(A)

    if tree.name=="atan" then
        set_infos(msprintf(gettext("If %s is imaginary and its module is > 1\n      the real part of %s is -π/2 in Scilab instead of +π/2 in Matlab."), strcat(expression2code(A), ""), strcat(expression2code(tree), "")),2)
    elseif tree.name=="acoth" then
        set_infos(msprintf(gettext("If %s is in [0,1)\n  imag(%s) is -π/2 in Scilab instead of +π/2 in Matlab."), strcat(expression2code(A), ""), strcat(expression2code(tree), "")),2)
    elseif tree.name=="asin" then
        set_infos(msprintf(gettext("If %s is outside [-1,1]\n   complex part of output of %s will be the opposite of Matlab one."), strcat(expression2code(A), ""), strcat(expression2code(tree), "")),2)
    else
		set_infos(msprintf(gettext("If %s < -1, complex part of output of %s will be the opposite of Matlab one."), strcat(expression2code(A), ""), strcat(expression2code(tree), "")),2)
	end
    tree.lhs(1).dims = A.dims
    // Property unknown because result can be complex for real input
    tree.lhs(1).type = Type(Double,Unknown)
endfunction
