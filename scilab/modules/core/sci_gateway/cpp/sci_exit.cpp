/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2015 - Scilab Enterprises - Anais AUBERT
 * Copyright (C) 2015 - Scilab Enterprises - Cedric Delamarre
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

#include "core_gw.hxx"
#include "function.hxx"
#include "configvariable.hxx"
#include "double.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
#include "sciprint.h"
#include "configvariable_interface.h" /* FIXME: enum scilabMode */
#include "createMainScilabObject.h"
}

types::Function::ReturnValue sci_exit(types::typed_list &in, int _iRetCount, types::typed_list &out)
{

    BOOL shouldExit = TRUE;
    double dExit = 0;
    // in[0] Should be a scalar double value.
    if (in.size() > 1)
    {
        Scierror(72, 0, 1);
        return types::Function::Error;
    }

    if (in.size() != 0)
    {
        types::InternalType* pIT = in[0];
        if (pIT->isDouble() == false)
        {
            Scierror(93, 1);
            return types::Function::Error;
        }

        types::Double* pD = pIT->getAs<types::Double>();
        if (pD->isScalar() == false)
        {
            Scierror(101, 1);
            return types::Function::Error;
        }

        dExit = pD->getFirst();
        if (dExit != (int) dExit)
        {
            Scierror(111, 1);
            return types::Function::Error;
        }
    }

    if (ConfigVariable::getScilabMode() != SCILAB_NWNI)
    {
        if (in.size() == 0)
        {
            shouldExit = canCloseMainScilabObject();
        }
        else
        {
            forceCloseMainScilabObject();
        }
    }

    if (shouldExit)
    {
        ConfigVariable::setExitStatus((int)dExit);
        ConfigVariable::setForceQuit(true);
        // go out without continue any execution
        throw ast::InternalAbort();
    }
    return types::Function::OK;
}
