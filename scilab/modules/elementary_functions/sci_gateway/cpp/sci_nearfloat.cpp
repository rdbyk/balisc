/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2018 - Stéphane Mottelet
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

#include <cfloat>
#include <cmath>
#include <complex>
#include "string.hxx"
#include "elem_func_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "overload.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Double;
using types::Function;
using types::InternalType;
using types::String;
using types::typed_list;

Function::ReturnValue sci_nearfloat(typed_list &in, int _iRetCount, typed_list &out)
{
    double dblMode;

    if (in.size() != 2)
    {
        Scierror(71, 2);
        return Function::Error;
    }

    if (_iRetCount > 1)
    {
        Scierror(81, 1);
        return Function::Error;
    }

    InternalType* pIT = in[0];
    if (pIT->isString())
    {
        String* pStr = pIT->getAs<String>();

        if (pStr->getSize() > 1)
        {
            Scierror(102, 1);
            return Function::Error;
        }

        wchar_t* wcsString = pStr->get(0);
        if (wcscmp(wcsString, L"succ") == 0)
        {
            dblMode = INFINITY;
        }
        else if (wcscmp(wcsString, L"pred") == 0)
        {
            dblMode = -INFINITY;
        }
        else
        {
            Scierror(110, 1, _("'succ' or 'pred'"));
            return Function::Error;
        }
    }
    else
    {
        Scierror(91, 1);
        return Function::Error;
    }

    pIT = in[1];
    if (pIT->isDouble() == false)
    {
        std::wstring wstFuncName = L"%" + pIT->getShortTypeStr() + L"_nearfloat";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }


    Double* pDblIn = pIT->getAs<Double>();
    if (pDblIn->isComplex())
    {
        Scierror(94, 2);
        return Function::Error;
    }

    Double* pDblOut = new Double(pDblIn->getDims(), pDblIn->getDimsArray());
    double *pdRealIn = pDblIn->get();
    double *pdRealOut = pDblOut->get();
    for (int i = 0; i < pDblIn->getSize(); ++i)
    {
        pdRealOut[i] = std::nextafter(pdRealIn[i], dblMode);
    }

    out.push_back(pDblOut);
    return Function::OK;
}
