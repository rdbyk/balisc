/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
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

#include "fileio_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "bool.hxx"
#include "double.hxx"

extern "C"
{
#include "localization.h"
#include "basename.h"
#include "Scierror.h"
}

types::Function::ReturnValue sci_basename(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int iExpand = 1;

    if (in.size() < 1 || in.size() > 3)
    {
        Scierror(72, 1, 3);
        return types::Function::Error;
    }

    if (in.size() > 2)
    {
        if (in[2]->isBool() == false)
        {
            Scierror(110, 3, _("scalar boolean"));
            return types::Function::Error;
        }

        if (in[2]->getAs<types::Bool>()->getSize() != 1)
        {
            Scierror(110, 3, _("scalar boolean"));
            return types::Function::Error;
        }

        iExpand = in[2]->getAs<types::Bool>()->get()[0];
    }

    if (in.size() > 1)
    {
        if (in[1]->isBool() == false)
        {
            Scierror(110, 2, _("scalar boolean"));
            return types::Function::Error;
        }

        if (in[1]->getAs<types::Bool>()->getSize() != 1)
        {
            Scierror(110, 2, _("scalar boolean"));
            return types::Function::Error;
        }
    }

    if (in[0]->isDouble() && in[0]->getAs<types::Double>()->isEmpty())
    {
        out.push_back(types::Double::Empty());
        return types::Function::OK;
    }
    if (in[0]->isString() == false)
    {
        Scierror(90, 1, _("matrix of strings"));
        return types::Function::Error;
    }

    types::String* pS = in[0]->getAs<types::String>();
    types::String* pOut = new types::String(pS->getRows(), pS->getCols());
    for (int i = 0 ; i < pS->getSize() ; i++)
    {
        wchar_t* base = basenameW(pS->get(i), (BOOL)iExpand);
        pOut->set(i, base);
        FREE(base);
    }

    out.push_back(pOut);
    return types::Function::OK;
}
