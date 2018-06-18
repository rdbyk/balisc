/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011-2011 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2014 - Scilab Enterprises - Anais AUBERT
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
#include "types.hxx"
#include "function.hxx"
#include "double.hxx"
#include "string.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "localization.h"
#include "Scierror.h"
#include "charEncoding.h"
}

#define DEFAULT_ERROR_CODE 10000

static const char fname[] = "error";

types::Function::ReturnValue sci_error(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1 && in.size() != 2)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d to %d expected.\n"), fname, 1, 2);
        return types::Function::Error;
    }

    if (in.size() == 1)
    {
        // RHS == 1
        if (in[0]->isString() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), fname, 1);
            return types::Function::Error;
        }

        types::String* pStrError = in[0]->getAs<types::String>();
        std::string strErr = "";
        char* pstError = NULL;
        for (int i = 0; i < pStrError->getSize() - 1; i++)
        {
            pstError = wide_string_to_UTF8(pStrError->get(i));
            strErr = strErr + std::string(pstError) + std::string("\n");
            FREE(pstError);
        }

        pstError = wide_string_to_UTF8(pStrError->get(pStrError->getSize() - 1));
        strErr = strErr + std::string(pstError);
        FREE(pstError);

        Scierror(DEFAULT_ERROR_CODE, "%s", strErr.c_str());
    }
    else
    {
        types::Double* pDbl = NULL;
        types::String* pStr = NULL;
        int iPosDouble = 1;
        int iPosString = 1;
        // RHS = 2 according to previous check.
        if (in[0]->isDouble() == false && in[0]->isString() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d.\n"), fname, 1);
            return types::Function::Error;
        }

        if (in[1]->isString() == false && in[1]->isDouble() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d.\n"), fname, 2);
            return types::Function::Error;
        }

        if ((in[0]->isDouble() == false && in[1]->isDouble() == false) ||
                (in[0]->isString() == false && in[1]->isString() == false) )
        {
            Scierror(999, _("%s: Wrong type for input argument #%d.\n"), fname, 2);
            return types::Function::Error;
        }

        if (in[0]->isDouble())
        {
            iPosString = 2;
            pDbl = in[0]->getAs<types::Double>();
            pStr = in[1]->getAs<types::String>();
        }
        else
        {
            iPosDouble = 2;
            pDbl = in[1]->getAs<types::Double>();
            pStr = in[0]->getAs<types::String>();
        }

        if (pDbl->isComplex())
        {
            Scierror(999, _("%s: Wrong type for input argument #%d.\n"), fname, iPosDouble);
            return types::Function::Error;
        }

        if (pDbl->isScalar() == false)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d.\n"), fname, iPosDouble);
            return types::Function::Error;
        }

        if (pStr->isScalar() == false)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d.\n"), fname, iPosString);
            return types::Function::Error;
        }

        if (pDbl->getFirst() <= 0)
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: Value greater than 0 expected.\n"), fname, iPosDouble);
            return types::Function::Error;
        }

        char* pst = wide_string_to_UTF8(pStr->getFirst());
        Scierror((int)pDbl->getFirst(), "%s\n", pst);
        FREE(pst);
    }

    return types::Function::Error;
}
