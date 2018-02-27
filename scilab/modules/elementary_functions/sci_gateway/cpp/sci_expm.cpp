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

static const char fname[] = "expm";

types::Function::ReturnValue sci_expm(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::Double* pDblIn = NULL;
    types::Double* pDblOut = NULL;

    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), fname, 1);
        return types::Function::Error;
    }

    if (in[0]->isDouble() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_expm";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    pDblIn = in[0]->getAs<types::Double>();

    if (pDblIn->getDims() > 2)
    {
        return Overload::call(L"%hm_expm", in, _iRetCount, out);
    }

    if (pDblIn->getSize() == 0)
    {
        out.push_back(types::Double::Empty());
        return types::Function::OK;
    }

    if (pDblIn->getCols() != pDblIn->getRows())
    {
        Scierror(999, _("%s: Wrong size for input argument #%d : A square matrix expected.\n"), fname, 1);
        return types::Function::Error;
    }

    bool bIsComplex = pDblIn->isComplex();

    if (pDblIn->getRows() == -1) // FIXME: find a better way to detect eye()
    {
        if (bIsComplex)
        {
            std::complex<double> z = std::exp(std::complex<double>(pDblIn->getFirst(), pDblIn->getImgFirst()));
            out.push_back(types::Double::Identity(real(z), imag(z)));
        }
        else
        {
            out.push_back(types::Double::Identity(std::exp(pDblIn->getFirst())));
        }

        return types::Function::OK;
    }

    pDblOut = new types::Double(pDblIn->getDims(), pDblIn->getDimsArray(), bIsComplex);

    if (bIsComplex)
    {
        zexpms2(pDblIn->get(), pDblIn->getImg(), pDblOut->get(), pDblOut->getImg(), pDblIn->getCols());
    }
    else
    {
        dexpms2(pDblIn->get(), pDblOut->get(), pDblIn->getCols());
    }

    out.push_back(pDblOut);
    return types::Function::OK;
}
