/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Allan CORNET
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2020 Dirk Reusch, Kybernetik Dr. Reusch
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
#include "bool.hxx"

extern "C"
{
#include "pathconvert.h"
#include "getshortpathname.h"
#include "sci_malloc.h"
#include "Scierror.h"
#include "localization.h"
}

types::Function::ReturnValue sci_getshortpathname(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71, 1);
        return types::Function::Error;
    }

    if (_iRetCount > 2)
    {
        Scierror(82, 1, 2);
        return types::Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(90, 1, _("matrix of strings"));
        return types::Function::Error;
    }

    types::String* pS = in[0]->getAs<types::String>();

    types::String* pOut1 = new types::String(pS->getRows(), pS->getCols());
    types::Bool* pOut2 = new types::Bool(pS->getRows(), pS->getCols());
    int* pBool = pOut2->get();
    wchar_t** p = pS->get();
    int size = pS->getSize();
    for (int i = 0; i < size; i++)
    {
        BOOL flagtrail = FALSE;
        wchar_t* tmp = getshortpathnameW(p[i], (BOOL*)&pBool[i]);
        int ilast = wcslen(p[i]) - 1;
        if (ilast)
        {
            wchar_t last = p[i][ilast];
            if (last == '\\' || last == '/')
            {
                flagtrail = TRUE;
            }
        }
        wchar_t* pwstPath = pathconvertW(tmp, flagtrail, FALSE, AUTO_STYLE);
        pOut1->set(i, pwstPath);
        FREE(pwstPath);
        FREE(tmp);
    }

    out.push_back(pOut1);
    if (_iRetCount == 2)
    {
        out.push_back(pOut2);
    }
    else
    {
        pOut2->killMe();
    }

    return types::Function::OK;
}
