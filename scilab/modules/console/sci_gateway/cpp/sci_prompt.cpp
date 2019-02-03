/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Cedric DELAMARRE
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "console_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "string.hxx"
#include "configvariable.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
#include "prompt.h"
#include "sci_malloc.h"
}

types::Function::ReturnValue sci_prompt(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() > 1)
    {
        Scierror(72, 0, 1);
        return types::Function::Error;
    }

    if (in.size() == 0)
    {
        if (_iRetCount > 2)
        {
            Scierror(82, 1, 2);
            return types::Function::Error;
        }

        const char* currentPrompt = GetCurrentPrompt();

        out.push_back(new types::String(currentPrompt));
        if (_iRetCount == 2)
        {
            types::Double* pDbl = new types::Double(1, 1);
            pDbl->set(0, ConfigVariable::getPauseLevel());
            out.push_back(pDbl);
        }
    }
    else
    {
        if (_iRetCount > 1)
        {
            Scierror(81, 1);
            return types::Function::Error;
        }

        if ((in[0]->isString() == false) || !in[0]->getAs<types::String>()->isScalar())
        {
            Scierror(91, 1);
            return types::Function::Error;
        }

        char* pstrPrompt = wide_string_to_UTF8(in[0]->getAs<types::String>()->getFirst());
        SetTemporaryPrompt(pstrPrompt);
        FREE(pstrPrompt);
    }

    return types::Function::OK;
}
