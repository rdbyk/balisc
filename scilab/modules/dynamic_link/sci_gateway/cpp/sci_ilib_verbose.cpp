/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) DIGITEO - 2009 - Allan CORNET
 * Copyright (C) DIGITEO - 2011 - Antoine ELIAS
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

#include "dynamic_link_gw.hxx"
#include "function.hxx"
#include "double.hxx"
extern "C"
{
#include "ilib_verbose.h"
#include "localization.h"
#include "Scierror.h"
}

types::Function::ReturnValue sci_ilib_verbose(types::typed_list &in, int _iRetCount, types::typed_list &out)
{

    if (in.size() > 1)
    {
        Scierror(72, 0, 1);
        return types::Function::Error;
    }

    if (in.size() == 0)
    {
        out.push_back(new types::Double((double)getIlibVerboseLevel()));
        return types::Function::OK;
    }

    if (in[0]->isDouble() == false || in[0]->getAs<types::Double>()->isScalar() == false)
    {
        Scierror(111, 1);
        return types::Function::Error;
    }

    int iLevel = (int) in[0]->getAs<types::Double>()->getFirst();
    if ((double)iLevel !=  in[0]->getAs<types::Double>()->getFirst())
    {
        Scierror(111, 1);
        return types::Function::Error;
    }

    if (!setIlibVerboseLevel((ilib_verbose_level)iLevel))
    {
        Scierror(110, 1, _("0, 1, or 2"));
        return types::Function::Error;
    }

    return types::Function::OK;
}
