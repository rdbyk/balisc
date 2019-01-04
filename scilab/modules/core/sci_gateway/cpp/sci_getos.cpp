/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Antoine ELIAS
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

#include "core_gw.hxx"
#include "function.hxx"
#include "string.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "getos.h"
#include "localization.h"
#include "Scierror.h"
}

types::Function::ReturnValue sci_getos(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 0)
    {
        Scierror(71, 0);
        return types::Function::Error;
    }

    if (_iRetCount > 2)
    {
        Scierror(82, 1, 2);
        return types::Function::Error;
    }

    char *OperatingSystem = getOSFullName();

    if (OperatingSystem)
    {
        types::String* pS1 = new types::String(OperatingSystem);
        out.push_back(pS1);
        FREE(OperatingSystem);

        if (_iRetCount == 2)
        {
            char *Release = getOSRelease();

            if (Release)
            {
                types::String* pS2 = new types::String(Release);
                out.push_back(pS2);
                FREE(Release);
            }
            else
            {
                Scierror(1);
                return types::Function::Error;
            }
        }
    }
    else
    {
        Scierror(1);
        return types::Function::Error;
    }

    return types::Function::OK;
}
