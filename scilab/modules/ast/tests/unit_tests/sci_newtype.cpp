/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2014 - Scilab Enterprises - Cedric Delamarre
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

#include "function.hxx"
#include "bool.hxx"
#include "newtype.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}


types::Function::ReturnValue sci_newtype(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() > 1)
    {
        Scierror(71, 1);
        return types::Function::Error;
    }

    if (_iRetCount > 1)
    {
        Scierror(81, 1);
        return types::Function::Error;
    }

    if (in.size() == 1)
    {
        types::Bool* pIn = in[0]->getAs<types::Bool>();
        if (pIn == NULL || pIn->isScalar() == false)
        {
            Scierror(91, 1, _("scalar boolean"));
            return types::Function::Error;
        }

        out.push_back(new NewType(pIn->get(0)));
    }
    else
    {
        out.push_back(new NewType());
    }

    return types::Function::OK;
}
