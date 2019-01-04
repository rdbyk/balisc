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

#include "elem_func_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "overload.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "expm.h"
}

using types::Double;
using types::Function;
using types::typed_list;

Function::ReturnValue sci_expm(typed_list &in, int _iRetCount, typed_list &out)
{
    Double* pDblIn = NULL;
    Double* pDblOut = NULL;

    if (in.size() != 1)
    {
        Scierror(71, 1);
        return Function::Error;
    }

    if (in[0]->isDouble() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_expm";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    pDblIn = in[0]->getAs<Double>();

    if (pDblIn->getDims() > 2)
    {
        return Overload::call(L"%hm_expm", in, _iRetCount, out);
    }

    if (pDblIn->getSize() == 0)
    {
        out.push_back(Double::Empty());
        return Function::OK;
    }

    if (pDblIn->getCols() != pDblIn->getRows())
    {
        Scierror(103, 1);
        return Function::Error;
    }

    bool bIsComplex = pDblIn->isComplex();

    if (pDblIn->getRows() == -1) // FIXME: find a better way to detect eye()
    {
        if (bIsComplex)
        {
            std::complex<double> z = std::exp(std::complex<double>(pDblIn->getFirst(), pDblIn->getImgFirst()));
            out.push_back(Double::Identity(real(z), imag(z)));
        }
        else
        {
            out.push_back(Double::Identity(std::exp(pDblIn->getFirst())));
        }

        return Function::OK;
    }

    pDblOut = new Double(pDblIn->getDims(), pDblIn->getDimsArray(), bIsComplex);

    // Note: NULL pointers for imaginary parts are handled in zexpms2
    zexpms2(pDblIn->get(), pDblIn->getImg(), pDblOut->get(), pDblOut->getImg(), pDblIn->getCols());

    out.push_back(pDblOut);
    return Function::OK;
}
