/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 Siddhartha Gairola
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

#include "string_gw.hxx"
#include "function.hxx"
#include "context.hxx"
#include "types.hxx"
#include "bool.hxx"
#include "double.hxx"
#include "stripblanks.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
}

types::Function::ReturnValue sci_stripblanks(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    bool bRemoveTab = false;
    double  flag = 0;

    if (in.size() < 1 || in.size() > 3)
    {
        Scierror(72, 1, 3);
        return types::Function::Error;
    }

    if (in.size() > 1)
    {
        if (in[1]->isBool() == false || in[1]->getAs<types::Bool>()->isScalar() == false)
        {
            Scierror(90, 2, _("scalar boolean"));
            return types::Function::Error;
        }

        if (in[1]->getAs<types::Bool>()->get()[0] == 1)
        {
            bRemoveTab = true;
        }
    }

    if (in.size() == 3)
    {
        if (in[2]->isDouble() == false || in[2]->getAs<types::Double>()->isScalar() == false)
        {

            Scierror(93, 2);
            return types::Function::Error;

        }

        flag = in[2]->getAs<types::Double>()->get()[0];

        if (floor(flag) != flag || (flag != 0.0 && flag != 1.0 && flag != -1.0))
        {

            Scierror(110, 3, _("-1, 0, or 1"));
            return types::Function::Error;
        }

    }

    switch (in[0]->getType())
    {
        case types::InternalType::ScilabString:
        {
            types::String *pS = stripblanks(in[0]->getAs<types::String>(), bRemoveTab, static_cast<int>(flag));
            if (pS == NULL)
            {
                Scierror(1);
                return types::Function::Error;
            }

            out.push_back(pS);
            break;
        }
        case types::InternalType::ScilabDouble://manage []
        {
            if (in[0]->getAs<types::Double>()->getSize() != 0)
            {
                Scierror(90, 1, _("matrix of strings or empty matrix"));
                return types::Function::Error;
            }

            out.push_back(types::Double::Empty());
            break;
        }
        default:
        {
            Scierror(90, 1, _("matrix of strings or empty matrix"));
            return types::Function::Error;
        }
    }

    return types::Function::OK;
}
