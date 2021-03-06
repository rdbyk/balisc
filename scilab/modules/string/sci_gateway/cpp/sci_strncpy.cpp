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
#include "double.hxx"
#include "funcmanager.hxx"
#include "string_gw.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "core_math.h"
#include "localization.h"
#include "Scierror.h"
}

types::Function::ReturnValue sci_strncpy(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::String* pString      = NULL;
    types::Double* pDouble      = NULL;
    types::String* pOutString   = NULL;

    if (in.size() != 2)
    {
        Scierror(71, 2);
        return types::Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(90, 1, _("matrix of strings"));
        return types::Function::Error;
    }

    if (in[1]->isDouble() == false)
    {
        Scierror(90, 2, _("matrix of integer values"));
        return types::Function::Error;
    }

    pString = in[0]->getAs<types::String>();
    pDouble = in[1]->getAs<types::Double>();

    if (pDouble->getSize() == 0)
    {
        Scierror(90, 2, _("non-empty real matrix"));
        return types::Function::Error;
    }

    //same dimension or 2nd arg scalar
    if (pString->getSize() != pDouble->getSize() && pDouble->isScalar() == false)
    {
        Scierror(100, 2, _("real scalar or matrix with same size as argument #1"));
        return types::Function::Error;
    }

    pOutString  = new types::String(pString->getDims(), pString->getDimsArray());

    int j = 0; /* Input parameter two is dimension one */
    for (int i = 0 ; i < pString->getSize() ; i++)
    {
        wchar_t *wcOutput   = NULL;
        int sizeOfCopy      = 0;

        if (pDouble->isScalar() == false)
        {
            j = i; /* Input parameter One & two have same dimension */
        }

        if (pDouble->get(j) < wcslen(pString->get(i)))
        {
            int iLen = (int)pDouble->get(j);
            if (iLen < 0)
            {
                iLen = 0;
            }

            wcOutput = (wchar_t*)MALLOC(sizeof(wchar_t) * (iLen + 1));
            sizeOfCopy = iLen;
        }
        else
        {
            int iLen = (int)wcslen(pString->get(i));
            wcOutput = (wchar_t*)MALLOC(sizeof(wchar_t) * (iLen + 1));
            sizeOfCopy = iLen;
        }

        if (wcOutput)
        {
            wcsncpy(wcOutput, pString->get(i), sizeOfCopy);
            wcOutput[sizeOfCopy] = L'\0';

            pOutString->set(i, wcOutput);
            FREE(wcOutput);
            wcOutput = NULL;
        }
        else
        {
            delete pOutString;
            Scierror(1);
            return types::Function::Error;
        }
    }

    out.push_back(pOutString);
    return types::Function::OK;
}
