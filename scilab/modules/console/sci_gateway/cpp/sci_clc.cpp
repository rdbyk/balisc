/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Cedric DELAMARRE
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
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

extern "C"
{
#include "localization.h"
#include "Scierror.h"
#include "clc.h"
#include "configvariable_interface.h"
}

types::Function::ReturnValue sci_clc(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    BOOL res = FALSE;
    int nblines = -1;

    if (in.size() == 0)
    {
        /* Clear console full */
        nblines = -1;
    }
    else if (in.size() == 1)
    {
        if ((in[0]->isDouble() == false) || !in[0]->getAs<types::Double>()->isScalar())
        {
            Scierror(93, 1);
            return types::Function::Error;
        }
        nblines = (int)in[0]->getAs<types::Double>()->getFirst();
        if (nblines < 0)
        {
            Scierror(110, 1, _("positive real"));
            return types::Function::Error;
        }
    }
    else
    {
        Scierror(72, 0, 1);
        return types::Function::Error;
    }

    res = clc(nblines);
    if (!res)
    {
        Scierror(140, getScilabModeString());
        return types::Function::Error;
    }

    return types::Function::OK;
}
