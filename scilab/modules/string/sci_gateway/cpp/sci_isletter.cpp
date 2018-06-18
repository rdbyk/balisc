/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) Digiteo 2011 - Cedric DELAMARRE
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


#include "function.hxx"
#include "string.hxx"
#include "list.hxx"
#include "bool.hxx"
#include "double.hxx"
#include "function.hxx"
#include "string_gw.hxx"

extern "C"
{
#include "core_math.h"
#include "localization.h"
#include "Scierror.h"
#include "isletter.h"
#include "BOOL.h"
}

static const char fname[] = "isletter";

types::Function::ReturnValue sci_isletter(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::Bool* pOutBool   = NULL;
    types::String* pString  = NULL;
    int dimsArray[2]        = {1, 0};
    BOOL *values            = NULL;

    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d expected.\n"), fname, 1);
        return types::Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: String expected.\n"), fname, 1);
        return types::Function::Error;
    }

    pString = in[0]->getAs<types::String>();
    if (pString->isScalar() == false)
    {
        Scierror(999, _("%s: Wrong size for input argument #%d.\n"), fname, 1);
        return types::Function::Error;
    }

    if (pString->getSize() == 0)
    {
        out.push_back(types::Double::Empty());
        return types::Function::OK;
    }

    values = isletterW(pString->getFirst(), &dimsArray[1]);

    if (dimsArray[1] > 0)
    {
        pOutBool  = new types::Bool(2, dimsArray);
        pOutBool->set((int *) values);
        out.push_back(pOutBool);
    }
    else
    {
        out.push_back(types::Double::Empty());
    }

    if (values)
    {
        FREE(values);
    }
    return types::Function::OK;
}
