/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyrigth (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "dynamic_link_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "string.hxx"

extern "C"
{
#include "addinter.h"
#include "localization.h"
#include "Scierror.h"
#include "dl_genErrorMessage.h"
}

types::Function::ReturnValue sci_addinter(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int iErr = 0;
    if (in.size() != 3)
    {
        Scierror(71, 3);
        return types::Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(91, 1);
        return types::Function::Error;
    }

    types::String* pSLibName = in[0]->getAs<types::String>();
    if (pSLibName->isScalar() == false)
    {
        Scierror(102, 1);
        return types::Function::Error;
    }

    if (in[1]->isString() == false)
    {
        Scierror(91, 2);
        return types::Function::Error;
    }

    types::String* pSModuleName = in[1]->getAs<types::String>();
    if (pSModuleName->isScalar() == false)
    {
        Scierror(102, 2);
        return types::Function::Error;
    }

    if (in[2]->isString() == false)
    {
        Scierror(91, 3);
        return types::Function::Error;
    }

    types::String* pSFunctionList = in[2]->getAs<types::String>();
    if (pSFunctionList->isVector() == false)
    {
        Scierror(110, 3, _("vector of strings"), "addinter", 3);
        return types::Function::Error;
    }

    iErr = AddInterfaceToScilab(pSLibName->getFirst(), pSModuleName->getFirst(), pSFunctionList->get(), pSFunctionList->getSize());
    if (iErr)
    {
        dl_genErrorMessage(L"addinter", iErr, pSLibName->getFirst());
        return types::Function::Error;
    }

    return types::Function::OK;
}
