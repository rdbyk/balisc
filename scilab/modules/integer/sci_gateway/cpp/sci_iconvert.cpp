/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2013 - Scilab Enterprises - Cedric Delamarre
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "integer_gw.hxx"
#include "function.hxx"
#include "overload.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Function;
using types::typed_list;

Function::ReturnValue sci_iconvert(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 2)
    {
        Scierror(71, 2);
        return Function::Error;
    }

    if (!(in[0]->isInt() || in[0]->isDouble() || in[0]->isBool()))
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_iconvert";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    return Overload::call(L"%_iconvert", in, _iRetCount, out);
}
