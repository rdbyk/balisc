/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011-2011 - DIGITEO - Bruno JOFRET
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

#include <string>

#include "core_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "scilabWrite.hxx"
#include "configvariable.hxx"

extern "C"
{
#include "charEncoding.h"
#include "sciprint.h"
#include "getos.h"
#include "localization.h"
#include "Scierror.h"
#include "sci_malloc.h"
#include "os_string.h"
#include "Sciwarning.h"
}

static const char fname[] = "warning";

types::Function::ReturnValue sci_warning(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::String *psInput = NULL;

    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d expected.\n"), fname, 1);
        return types::Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: String expected.\n"), fname, 1);
        return types::Function::Error;
    }

    psInput = in[0]->getAs<types::String>();

    if (psInput->getSize() == 1)
    {
        wchar_t* arg = psInput->getFirst();

        /* "on" "off" "query" "stop" */
        if (wcscmp(arg, L"on") == 0)
        {
            ConfigVariable::setWarningMode(true);
            ConfigVariable::setWarningStop(false);
            return types::Function::OK;
        }

        if (wcscmp(arg, L"off") == 0)
        {
            ConfigVariable::setWarningMode(false);
            ConfigVariable::setWarningStop(false);
            return types::Function::OK;
        }

        if (wcscmp(arg, L"stop") == 0)
        {
            ConfigVariable::setWarningMode(true);
            ConfigVariable::setWarningStop(true);
            return types::Function::OK;
        }

        if (wcscmp(arg, L"query") == 0)
        {
            if (ConfigVariable::getWarningMode())
            {
                if (ConfigVariable::getWarningStop())
                {
                    // WarningMode and WarningStop => warning stop mode active
                    out.push_back(new types::String(L"stop"));
                }
                else
                {
                    // WarningMode and !WarningStop => warning on  mode active
                    out.push_back(new types::String(L"on"));
                }
            }
            else
            {
                out.push_back(new types::String(L"off"));
            }
            return types::Function::OK;
        }
    }

    if (ConfigVariable::getWarningMode())
    {
        for (int i = 0; i < psInput->getSize() ; ++i)
        {
            wchar_t* pwstTemp = psInput->get(i);
            std::wstring warning = _W("WARNING: %ls\n");
            size_t iSize = (wcslen(pwstTemp) + warning.size() + 1);

            wchar_t* pwstToPrint = (wchar_t*)MALLOC(sizeof(wchar_t) * iSize);
            os_swprintf(pwstToPrint, iSize, warning.c_str(), pwstTemp);
            pwstToPrint[iSize - 1] = L'\0';

            scilabForcedWriteW(pwstToPrint);
            FREE(pwstToPrint);
        }

        if (ConfigVariable::getWarningStop())
        {
            Sciwarning("");
        }
    }


    return types::Function::OK;
}
