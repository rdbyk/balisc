/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
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
#include "configvariable.hxx"
#include "double.hxx"
#include "function.hxx"

extern "C"
{
#include "Scierror.h"
#include "sciprint.h"
#include "localization.h"
}

types::Function::ReturnValue sci_mode(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::InternalType *pIT = NULL;

    if (in.size() > 1)
    {
        Scierror(73 , 0, 1);
        return types::Function::Error;
    }

    if (in.size() == 0)
    {
        out.push_back(new types::Double(ConfigVariable::getPromptMode()));
    }
    else
    {
        if (in[0]->isDouble() == false)
        {
            Scierror(93, 1);
            return types::Function::Error;
        }

        types::Double* pDblIn = in[0]->getAs<types::Double>();

        if (pDblIn->isScalar() == false)
        {
            Scierror(101, 1);
            return types::Function::Error;
        }

        int iScilabMode = (int)pDblIn->getFirst();
        if (pDblIn->getFirst() != (double)iScilabMode)
        {
            Scierror(111, 1);
            return types::Function::Error;
        }

        ConfigVariable::setPromptMode(iScilabMode);

        if (ConfigVariable::isPrintInteractive())
        {
            sciprint(_("Pause mode: enter empty lines to continue.\n"));
        }
    }

    return types::Function::OK;
}
