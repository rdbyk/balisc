/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Antoine ELIAS
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
#include "callable.hxx"
#include "context.hxx"
#include "string.hxx"
#include "bool.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

types::Function::ReturnValue sci_isglobal(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::typed_list::iterator inIterator;
    int iWrongType = 1;

    if (in.size() != 1)
    {
        Scierror(71, 1);
        return types::Function::Error;
    }
    else
    {
        if (in[0]->isString() == false)
        {
            Scierror(91, 1);
            return types::Function::Error;
        }

        types::String* pS = in[0]->getAs<types::String>();
        if (pS->isScalar() == false)
        {
            Scierror(91, 1);
            return types::Function::Error;
        }

        if (symbol::Context::getInstance()->isGlobalVisible(symbol::Symbol(pS->getFirst())))
        {
            out.push_back(new types::Bool(1));
        }
        else
        {
            out.push_back(new types::Bool(0));
        }
    }
    return types::Function::OK;
}
