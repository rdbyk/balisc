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

extern "C"
{
#include "localization.h"
#include "Scierror.h"
#include "tohome.h"
#include "configvariable_interface.h"
}

types::Function::ReturnValue sci_tohome(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 0)
    {
        Scierror(71, 0);
        return types::Function::Error;
    }
    if (!tohome())
    {
        Scierror(140, getScilabModeString());
        return types::Function::Error;
    }

    return types::Function::OK;
}
