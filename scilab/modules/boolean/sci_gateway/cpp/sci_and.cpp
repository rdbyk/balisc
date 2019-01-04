/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Allan CORNET
 * Copyright (C) DIGITEO - 2012 - Allan CORNET
 * Copyright (C) 2014 - Scilab Enterprises - Anais AUBERT
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

#include "boolean_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "overload.hxx"
#include "types.hxx"
#include "bool.hxx"
#include "double.hxx"

extern "C"
{
#include <string.h>
#include "Scierror.h"
#include "localization.h"
#include "usewmemcmp.h"
}

using types::Bool;
using types::Double;
using types::Function;
using types::GenericType;
using types::String;
using types::typed_list;

static void and_all(const int *v, int m, int n, int *r);
static void and_rows(const int *v, int m, int n, int *r);
static void and_cols(const int *v, int m, int n, int *r);

Function::ReturnValue sci_and(typed_list &in, int _iRetCount, typed_list &out)
{
    if ((in.size() < 1) || (in.size() > 2))
    {
        Scierror(72, 1, 2);
        return Function::Error;
    }

    if (in[0]->isGenericType() && in[0]->getAs<GenericType>()->getDims() > 2)
    {
        // hypermatrices are managed in external macro
        return Overload::call(L"%hm_and", in, _iRetCount, out);
    }

    if (in[0]->isBool() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_and";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    if (in.size() == 1)
    {
        Bool *pboolOut = new Bool(1, 1);
        Bool *pboolIn = in[0]->getAs<Bool>();
        and_all(pboolIn->get(), pboolIn->getRows(), pboolIn->getCols(), pboolOut->get());
        out.push_back(pboolOut);
        return Function::OK;
    }
    else if (in.size() == 2)
    {
        if (in[1]->getAs<GenericType>()->isScalar() == false)
        {
            Scierror(100, 2, _("real scalar or a string"));
            return Function::Error;
        }

        if (in[1]->isString())
        {
            Bool *pboolIn = in[0]->getAs<Bool>();
            int iRows = pboolIn->getRows();
            int iCols = pboolIn->getCols();

            wchar_t *pStr = in[1]->getAs<String>()->getFirst();
            bool bNotLengthOne = pStr[0] == L'\0' || pStr[1];

            switch (pStr[0])
            {
                case 'r':
                {
                    Bool *pboolOut = new Bool(1, iCols);
                    and_rows(pboolIn->get(), iRows, iCols, pboolOut->get());
                    out.push_back(pboolOut);
                    return Function::OK;
                }
                case 'c':
                {
                    Bool *pboolOut = new Bool(iRows, 1);
                    and_cols(pboolIn->get(), iRows, iCols, pboolOut->get());
                    out.push_back(pboolOut);
                    return Function::OK;
                }
                default:
                {
                    Scierror(110, 2, _("'r' or 'c'"));
                    return Function::Error;
                }
            }

            if (bNotLengthOne)
            {
                Scierror(110, 2, _("'r' or 'c'"));
                return Function::Error;
            }
        }
        else if (in[1]->isDouble())
        {
            Double *pdblIn = in[1]->getAs<Double>();
            if (pdblIn->isComplex())
            {
                Scierror(111, 2);
                return Function::Error;
            }

            int opt = static_cast<int>(pdblIn->getFirst());
            if (opt != pdblIn->getFirst())
            {
                Scierror(111, 2);
                return Function::Error;
            }

            Bool *pboolIn = in[0]->getAs<Bool>();
            int iRows = pboolIn->getRows();
            int iCols = pboolIn->getCols();

            switch (opt)
            {
                case 1:
                {
                    Bool *pboolOut = new Bool(1, iCols);
                    and_rows(pboolIn->get(), iRows, iCols, pboolOut->get());
                    out.push_back(pboolOut);
                    return Function::OK;
                }
                case 2:
                {
                    Bool *pboolOut = new Bool(iRows, 1);
                    and_cols(pboolIn->get(), iRows, iCols, pboolOut->get());
                    out.push_back(pboolOut);
                    return Function::OK;
                }
                default:
                {
                    Scierror(110, 2, _("1 or 2"));
                    return Function::Error;
                }
            }
        }
        else
        {
            Scierror(90, _("real scalar or a string"));
            return Function::Error;
        }
    }
}

void and_all(const int *v, int m, int n, int *r)
{
#ifdef USE_WMEMCMP
    wchar_t* vv = (wchar_t*)v;

    r[0] = *vv == TRUE && wmemcmp(vv, (wchar_t*)v + 1, m * n - 1) == 0;
#else
    int k = 0;

    r[0] = TRUE;

    for (k = 0; k < m * n; k++)
    {
        if (!v[k])
        {
            r[0] = FALSE;
            break;
        }
    }
#endif /* USE_WMEMCMP */
}

void and_rows(const int *v, int m, int n, int *r)
{
    int k = 0;

    for (k = 0; k < n; k++)
    {
#ifdef USE_WMEMCMP
        wchar_t* vr = (wchar_t*)(v + k * m);
        wchar_t* vvr = vr;

        r[k] = *vvr == TRUE && wmemcmp(vvr, vr + 1, m - 1) == 0;
#else
        int l = 0;
        int i = k * m;

        r[k] = TRUE;

        for (l = 0; l < m; l++)
        {
            if (!v[i++])
            {
                r[k] = FALSE;
                break;
            }
        }
#endif /* USE_WMEMCMP */
    }
}

void and_cols(const int *v, int m, int n, int *r)
{
    int l = 0;

    for (l = 0; l < m; l++)
    {
        int k = 0;
        int i = l;

        r[l] = TRUE;

        for (k = 0; k < n; k++)
        {
            if (!v[i])
            {
                r[l] = FALSE;
                break;
            }
            i += m;
        }
    }
}
