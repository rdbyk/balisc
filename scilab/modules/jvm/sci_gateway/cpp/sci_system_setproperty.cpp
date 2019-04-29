/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Allan CORNET
 * Copyright (C) 2015 - Scilab Enterprises - Vincent COUVERT
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

#include "jvm_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "double.hxx"

extern "C"
{
#include <string.h>
#include "system_setproperty.h"
#include "Scierror.h"
#include "localization.h"
#include "sci_malloc.h"
}

types::Function::ReturnValue sci_system_setproperty(types::typed_list &in, int _piRetCount, types::typed_list &out)
{
    if (in.size() != 2)
    {
        Scierror(71, 2);
        return types::Function::Error;
    }

    if (in[0]->isString() == false || in[0]->getAs<types::String>()->getSize() != 1)
    {
        Scierror(91, 1);
        return types::Function::Error;
    }

    if (in[1]->isString() == false || in[1]->getAs<types::String>()->getSize() != 1)
    {
        Scierror(91, 2);
        return types::Function::Error;
    }

    char* pstProperty        = wide_string_to_UTF8(in[0]->getAs<types::String>()->getFirst());
    char* pstValue           = wide_string_to_UTF8(in[1]->getAs<types::String>()->getFirst());
    char* pstPreviousValue   = system_setproperty(pstProperty, pstValue);

    FREE(pstProperty);
    FREE(pstValue);

    if (pstPreviousValue)
    {
        types::String* pSPreviousValue = new types::String(pstPreviousValue);
        out.push_back(pSPreviousValue);
        FREE(pstPreviousValue);
    }
    else
    {
        types::Double* pDPreviousValue = types::Double::Empty();
        out.push_back(pDPreviousValue);
    }
    return types::Function::OK;

}
