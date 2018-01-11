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
#include "vect_or.h"
}

using types::Bool;
using types::Double;
using types::Function;
using types::GenericType;
using types::String;
using types::typed_list;

Function::ReturnValue sci_or(typed_list &in, int _iRetCount, typed_list &out)
{
    int opt = 0;
    int* pBoolValuesOne = NULL;

    if ((in.size() < 1) || (in.size() > 2))
    {
        Scierror(999, _("%s: Wrong number of input arguments: %d to %d expected.\n"), "or", 1, 2);
        return Function::Error;
    }

    if (_iRetCount > 1)
    {
        Scierror(999, _("%s: Wrong number of output arguments: %d expected.\n"), "or", 1);
        return Function::Error;
    }

    if (in[0]->isGenericType() && in[0]->getAs<GenericType>()->getDims() > 2)
    {
        // hypermatrices are managed in external macro
        return Overload::call(L"%hm_or", in, _iRetCount, out);
    }

    if (in[0]->isBool() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_or";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    if (in.size() == 2)
    {
        if (in[1]->getAs<GenericType>()->isScalar() == false)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d.\n"), "or", 2);
            return Function::Error;
        }

        if (in[1]->isString())
        {
            wchar_t *pStr = in[1]->getAs<String>()->getFirst();
            bool bNotLengthOne = pStr[0] == L'\0' || pStr[1];

            switch (pStr[0])
            {
                case 'r':
                {
                    opt = OR_BY_ROWS;
                }
                break;
                case 'c':
                {
                    opt = OR_BY_COLUMNS;
                }
                break;
                default:
                {
                    Scierror(44, _("%s: Wrong value for input argument #%d.\n"), "or", 2);
                    return Function::Error;
                }
                break;
            }

            if (bNotLengthOne)
            {
                Scierror(44, _("%s: Wrong value for input argument #%d.\n"), "or", 2);
                return Function::Error;
            }

        }
        else if (in[1]->isDouble())
        {
            Double *pdblIn = in[1]->getAs<Double>();

            if (pdblIn->isComplex())
            {
                Scierror(44, _("%s: Wrong value for input argument #%d.\n"), "or", 2);
                return Function::Error;

            }

            opt = static_cast<int>(pdblIn->getFirst());
            if (opt != pdblIn->getFirst())
            {
                Scierror(999, _("%s: Wrong value for input argument #%d: An integer value expected.\n"), "or", 2);
                return Function::Error;
            }
        }
        else
        {
            Scierror(999, _("%s: Wrong type for input argument #%d.\n"), "or", 2);
            return Function::Error;
        }
    }

    Bool *pboolIn = in[0]->getAs<Bool>();
    int rowIn = pboolIn->getRows();
    int colIn = pboolIn->getCols();
    pBoolValuesOne = pboolIn->get();

    int rowOut = 1;
    int colOut = 1;

    if (opt > 2)
    {
        Scierror(999, _("%s: Wrong value for input argument #%d.\n"), "or", 2);
        return Function::Error;
    }

    switch (opt)
    {
        case OR_BY_ROWS:
            colOut = colIn;
            break;
        case OR_BY_COLUMNS:
            rowOut = rowIn;
            break;
    }

    Bool *pboolOut = new Bool(rowOut, colOut);
    vect_or(pBoolValuesOne, rowIn, colIn, pboolOut->get(), opt);

    out.push_back(pboolOut);
    return Function::OK;
}
