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
#include "funcmanager.hxx"
#include "string_gw.hxx"

extern "C"
{
#include "freeArrayOfPtrs.h"
#include "core_math.h"
#include "localization.h"
#include "Scierror.h"
#include "stringsstrrev.h"
}

static const char fname[] = "strrev";

types::Function::ReturnValue sci_strrev(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d expected.\n"), fname, 1);
        return types::Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: Matrix of Strings expected.\n"), fname, 1);
        return types::Function::Error;
    }

    types::String* pString = in[0]->getAs<types::String>();
    wchar_t **OutputStrings = strings_strrev(pString->get(), pString->getSize());
    types::String* pOutString = new types::String(pString->getDims(), pString->getDimsArray());

    pOutString->set(OutputStrings);
    freeArrayOfPtrs((void**)OutputStrings, pString->getSize());

    out.push_back(pOutString);
    return types::Function::OK;
}
