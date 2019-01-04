/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - DIGITEO - Cedric DELAMARRE
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

#include <complex>

#include "elem_func_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "overload.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "elem_common.h"
}

types::Function::ReturnValue sci_asinh(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::Double* pDblIn = NULL;
    types::Double* pDblOut = NULL;

    if (in.size() != 1)
    {
        Scierror(71, 1);
        return types::Function::Error;
    }

    if (in[0]->isDouble())
    {
        pDblIn = in[0]->getAs<types::Double>();
        pDblOut = new types::Double(pDblIn->getDims(), pDblIn->getDimsArray(), pDblIn->isComplex());

        double* pInR = pDblIn->get();
        double* pOutR = pDblOut->get();
        int size = pDblIn->getSize();
        if (pDblIn->isComplex())
        {
            double* pInI = pDblIn->getImg();
            double* pOutI = pDblOut->getImg();

            for (int i = 0; i < size; i++)
            {
                std::complex<double> c(pInR[i], pInI[i]);
                std::complex<double> d = std::asinh(c);
                pOutR[i] = d.real();
                pOutI[i] = d.imag();
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                pOutR[i] = asinh(pInR[i]);
            }
        }

        out.push_back(pDblOut);
    }
    else
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_asinh";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    return types::Function::OK;
}
