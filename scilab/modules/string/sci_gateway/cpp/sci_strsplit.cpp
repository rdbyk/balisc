/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2013 - Scilab Enterprises - Cedric Delamarre
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

#include "string_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "double.hxx"
#include "bool.hxx"
#include "overload.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "Scierror.h"
#include "localization.h"
#include "strsplit.h"
#include "freeArrayOfPtrs.h"
}

static const char fname[] = "strsplit";

types::Function::ReturnValue sci_strsplit(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::String* pStrIn = NULL;
    int iValueThree = 0;

    if (in.size() < 1 || in.size() > 3)
    {
        Scierror(72, 1, 3);
        return types::Function::Error;
    }

    if (_iRetCount > 2)
    {
        Scierror(82, 1, 2);
        return types::Function::Error;
    }

    // [[], ""] = strsplit([],...)
    if (in[0]->isDouble() && in[0]->getAs<types::Double>()->isEmpty())
    {
        out.push_back(types::Double::Empty());

        if (_iRetCount == 2)
        {
            out.push_back(new types::String(L""));
        }

        return types::Function::OK;
    }

    if (in[0]->isString() == false)
    {
        Scierror(91, 1);
        return types::Function::Error;
    }

    pStrIn = in[0]->getAs<types::String>();

    if (pStrIn->isScalar() == false)
    {
        Scierror(102, 1);
        return types::Function::Error;
    }

    if (in.size() > 2)
    {
        if (in[2]->isDouble() == false)
        {
            Scierror(93, 3);
            return types::Function::Error;
        }

        types::Double* pDblIn = in[2]->getAs<types::Double>();

        if (pDblIn->isScalar() == false)
        {
            Scierror(101, 3);
            return types::Function::Error;
        }

        iValueThree = (int)pDblIn->getFirst();

        if ( (double)iValueThree != pDblIn->getFirst())
        {
            Scierror(110, 3, _("positive integer value"));
            return types::Function::Error;
        }

        if ((iValueThree < 1) && (iValueThree != -1))
        {
            Scierror(110, 3, _("positive integer value"));
            return types::Function::Error;
        }
    }

    if (in.size() > 1)
    {
        if (in[1]->isDouble())
        {
            types::Double* pDbl = in[1]->getAs<types::Double>();

            if (_iRetCount == 2)
            {
                Scierror(81, 1);
                return types::Function::Error;
            }

            if (pDbl->getRows() != 1 && pDbl->getCols() != 1)
            {
                Scierror(100, 2, _("real vector"));
                return types::Function::Error;
            }

            strsplit_error ierr = STRSPLIT_NO_ERROR;
            wchar_t **results = strsplit(pStrIn->getFirst(), pDbl->get(), pDbl->getSize(), &ierr);

            switch (ierr)
            {
                case STRSPLIT_NO_ERROR:
                {
                    types::String* pStrOut = new types::String(pDbl->getSize() + 1, 1);
                    pStrOut->set(results);

                    freeArrayOfPtrs((void**)results, pDbl->getSize() + 1);
                    out.push_back(pStrOut);
                    return types::Function::OK;
                }
                break;
                case STRSPLIT_INCORRECT_VALUE_ERROR:
                {
                    freeArrayOfPtrs((void**)results, pDbl->getSize() + 1);
                    Scierror(110, 2, _("values less or equal than string length"));
                    return types::Function::Error;
                }
                break;
                case STRSPLIT_INCORRECT_ORDER_ERROR:
                {
                    freeArrayOfPtrs((void**)results, pDbl->getSize() + 1);
                    Scierror(102, 2, _("elements in increasing order"));
                    return types::Function::Error;
                }
                break;
                case STRSPLIT_MEMORY_ALLOCATION_ERROR:
                {
                    freeArrayOfPtrs((void**)results, pDbl->getSize() + 1);
                    Scierror(1);
                    return types::Function::Error;
                }
                break;
                default:
                {
                    freeArrayOfPtrs((void**)results, pDbl->getSize() + 1);
                    Scierror(0);
                    return types::Function::Error;
                }
                break;
            }
        }
        else if (in[1]->isString())
        {
            types::String* pStr = in[1]->getAs<types::String>();
            if (pStr->isScalar() == false)
            {
                // checks that 2nd parameter is not an array of regexp pattern
                wchar_t** pwcsStr = pStr->get();
                for (int i = 0; i < pStr->getSize(); i++)
                {
                    if (pwcsStr[i])
                    {
                        int iLen = (int)wcslen(pwcsStr[i]);
                        if (iLen > 2 && pwcsStr[i][0] == L'/' && pwcsStr[i][iLen - 1] == L'/')
                        {
                            Scierror(110, 2, _("regexp pattern is not"));
                            return types::Function::Error;
                        }
                    }
                }
            }
        }
        else
        {
            Scierror(90, 2, _("real vector or matrix of strings"));
            return types::Function::Error;
        }
    }

    return Overload::call(L"%_strsplit", in, _iRetCount, out);
}
