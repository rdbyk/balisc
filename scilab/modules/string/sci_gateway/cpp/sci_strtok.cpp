/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) Digiteo 2011 - Cedric DELAMARRE
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


#include "function.hxx"
#include "double.hxx"
#include "string.hxx"
#include "list.hxx"
#include "funcmanager.hxx"
#include "string_gw.hxx"

extern "C"
{
#include "core_math.h"
#include "localization.h"
#include "Scierror.h"
#include "os_string.h"
#include "os_wcstok.h"
#include <stdio.h>
}

types::Function::ReturnValue sci_strtok(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    static wchar_t *pwstState  = NULL;
    wchar_t *pwstString = NULL;
    wchar_t* pwstSeps = NULL;

    if (in.size() < 1 || in.size() > 2)
    {
        Scierror(72, 1, 2);
        return types::Function::Error;
    }

    if (in[0]->isString() == false || in[0]->getAs<types::String>()->isScalar() == false)
    {
        Scierror(91, 1);
        return types::Function::Error;
    }

    if (in.size() == 2 && (in[1]->isString() == false || in[1]->getAs<types::String>()->isScalar() == false))
    {
        Scierror(91, 2);
        return types::Function::Error;
    }

    if (in.size() == 1)
    {
        pwstSeps    = in[0]->getAs<types::String>()->getFirst();
    }
    else
    {
        pwstString = StringModule::setToken(in[0]->getAs<types::String>()->get()[0]);
        pwstSeps    = in[1]->getAs<types::String>()->getFirst();
        pwstState   = NULL;

        if (pwstString[0] == L'\0')
        {
            out.push_back(new types::String(L""));
            return types::Function::OK;
        }
    }

    wchar_t* pwstToken = NULL;
    if (pwstString == NULL && pwstState == NULL)
    {
        // set an empty string
        pwstToken = L"";
    }
    else
    {
        pwstToken = os_wcstok(pwstString, pwstSeps, &pwstState);
    }

    if (pwstToken)
    {
        out.push_back(new types::String(pwstToken));
    }
    else
    {
        StringModule::deleteToken();
        out.push_back(new types::String(L""));
    }

    return types::Function::OK;
}
