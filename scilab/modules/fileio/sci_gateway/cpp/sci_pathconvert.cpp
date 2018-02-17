/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
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

#include "fileio_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "double.hxx"
#include "bool.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "localization.h"
#include "Scierror.h"
#include "pathconvert.h"
}

#define UNIX_TYPE       L"u"
#define WINDOWS_TYPE    L"w"
#define _UNIX_TYPE      "u"
#define _WINDOWS_TYPE   "w"

static const char fname[] = "pathconvert";

types::Function::ReturnValue sci_pathconvert(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    PathConvertType PType   = AUTO_STYLE;
    int iPathExpand         = 1;
    int iPathTrail          = 1;

    if (in.size() < 1 || in.size() > 4)
    {
        Scierror(999, _("%s: Wrong number of input arguments: %d to %d expected.\n"), fname , 1, 4);
        return types::Function::Error;
    }

    //get type
    if (in.size() > 3)
    {
        if (in[3]->isString() == false || in[3]->getAs<types::String>()->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), fname, 4);
            return types::Function::Error;
        }

        wchar_t* pwstType = in[3]->getAs<types::String>()->getFirst();
        if (wcscmp(pwstType, WINDOWS_TYPE) == 0)
        {
            PType = WINDOWS_STYLE;
        }
        else if (wcscmp(pwstType, UNIX_TYPE) == 0)
        {
            PType = UNIX_STYLE;
        }
        else
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: '%s' or '%s' expected.\n"), fname, 4, _UNIX_TYPE, _WINDOWS_TYPE);
            return types::Function::Error;
        }
    }

    if (in.size() > 2)
    {
        if (in[2]->isBool() == false || in[2]->getAs<types::Bool>()->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: A boolean expected.\n"), fname, 3);
            return types::Function::Error;
        }

        iPathExpand = in[2]->getAs<types::Bool>()->get()[0];
    }

    if (in.size() > 1)
    {
        if (in[1]->isBool() == false || in[1]->getAs<types::Bool>()->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: A boolean expected.\n"), fname, 2);
            return types::Function::Error;
        }

        iPathTrail = in[1]->getAs<types::Bool>()->get()[0];
    }

    if (in[0]->isDouble() && in[0]->getAs<types::Double>()->isEmpty())
    {
        out.push_back(types::Double::Empty());
        return types::Function::OK;
    }

    if (in[0]->isString() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: Matrix of strings expected.\n"), fname, 1);
        return types::Function::Error;
    }

    types::String* pS = in[0]->getAs<types::String>();
    types::String* pOut = new types::String(pS->getRows(), pS->getCols());
    wchar_t** pStr = pOut->get();


    for (int i = 0 ; i < pS->getSize() ; i++)
    {
        pStr[i] = pathconvertW(pS->get(i), (BOOL) iPathTrail, (BOOL) iPathExpand, PType);
    }

    out.push_back(pOut);
    return types::Function::OK;
}
