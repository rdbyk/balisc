/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2013 - Scilab Enterprises - Cedric Delamarre
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "string_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "double.hxx"
#include "bool.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "Scierror.h"
#include "localization.h"
#include "isalphanum.h"
}

types::Function::ReturnValue sci_isalphanum(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::String* pStrIn   = NULL;
    types::Bool* pBOut      = NULL;
    wchar_t* wcstrIn        = NULL;
    int iResultSize         = 0;

    if (in.size() != 1)
    {
        Scierror(71, 1);
        return types::Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(91, 1);
        return types::Function::Error;
    }

    pStrIn = in[0]->getAs<types::String>();

    if (pStrIn->isScalar() == false)
    {
        Scierror(102, 1);
        return types::Function::Error;
    }

    wcstrIn = pStrIn->getFirst();
    int* pbResult = (int*)isalphanumW(wcstrIn, &iResultSize);
    if (pbResult == NULL)
    {
        out.push_back(types::Double::Empty());
        return types::Function::OK;
    }

    pBOut = new types::Bool(1, iResultSize);
    pBOut->set(pbResult);
    FREE(pbResult);
    out.push_back(pBOut);

    return types::Function::OK;
}
