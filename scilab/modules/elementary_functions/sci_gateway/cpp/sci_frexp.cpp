/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - DIGITEO - Cedric DELAMARRE
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
using types::typed_list;

Function::ReturnValue sci_frexp(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71, 1);
        return Function::Error;
    }

    if (in[0]->isDouble() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_frexp";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    Double* pDblIn = in[0]->getAs<Double>();

    if (pDblIn->isComplex())
    {
        Scierror(94, 1);
        return Function::Error;
    }

    Double* pDblCoef = new Double(pDblIn->getDims(), pDblIn->getDimsArray());
    Double* pDblExp  = new Double(pDblIn->getDims(), pDblIn->getDimsArray());

    double* pIn = pDblIn->get();
    double* pCoef = pDblCoef->get();
    double* pFrexp = pDblExp->get();
    int size = pDblIn->getSize();

    for (int i = 0; i < size; i++)
    {
        int iExp;
        pCoef[i] = std::frexp(pIn[i], &iExp);
        pFrexp[i] = static_cast<double>(iExp);
    }

    out.push_back(pDblCoef);
    out.push_back(pDblExp);

    return Function::OK;
}
