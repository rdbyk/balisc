/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "elem_func_gw.hxx"
#include "bool.hxx"
#include "function.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Bool;
using types::Function;
using types::typed_list;

Function::ReturnValue sci_isequal(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() <= 1)
    {
        Scierror(71, 1);
        return Function::Error;
    }

    int n = static_cast<int>(in.size());

    while(--n > 0 && *(in[n]) == *(in[0]));

    out.push_back(new Bool(n == 0));
    return Function::OK;
}
