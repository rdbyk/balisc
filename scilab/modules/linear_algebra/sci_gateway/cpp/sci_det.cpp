/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Cedric DELAMARRE
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

#include "linear_algebra_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "overload.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
#include "det.h"
#include "doublecomplex.h"
}

using types::Double;
using types::Function;
using types::typed_list;

static const char fname[] = "det";

Function::ReturnValue sci_det(typed_list &in, int _iRetCount, typed_list &out)
{
    Double* pDbl             = NULL;
    Double* pDblMantissa     = NULL;
    Double* pDblExponent     = NULL;
    double* pData                   = NULL;

    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d expected.\n"), fname, 1);
        return Function::Error;
    }

    if (_iRetCount > 2)
    {
        Scierror(78, _("%s: Wrong number of output arguments: %d to %d expected.\n"), fname, 1, 2);
        return Function::Error;
    }

    if ((in[0]->isDouble() == false))
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_det";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    Double* in0 = in[0]->getAs<Double>();

    if (in0->getRows() != in0->getCols())
    {
        Scierror(20, _("%s: Wrong type for input argument #%d: Square matrix expected.\n"), fname, 1);
        return Function::Error;
    }

    if ((in0->getSize() == 0)) // empty []
    {
        if (_iRetCount == 2)
        {
            out.push_back(new Double(0.0));
        }

        out.push_back(new Double(1.0));
        return Function::OK;
    }

    bool bIsComplex = in0->isComplex();

    if (bIsComplex)
    {
        pData = (double *)oGetDoubleComplexFromPointer(in0->getReal(), in0->getImg(), in0->getSize());
        if (!pData)
        {
            Scierror(999, _("%s: Cannot allocate more memory.\n"), fname);
            return Function::Error;
        }
    }
    else
    {
        pDbl = in0->clone()->getAs<Double>();
        pData = pDbl->getReal();
    }

    pDblMantissa = new Double(1, 1, bIsComplex);

    int iExponent = 0;
    int iRet = iDetM(pData, std::abs(in0->getCols()), pDblMantissa->getReal(), bIsComplex ? pDblMantissa->getImg() : NULL, (_iRetCount == 2) ? &iExponent : NULL);
    if (iRet < 0)
    {
        delete pDblMantissa;

        if (bIsComplex)
        {
            vFreeDoubleComplexFromPointer((doublecomplex*)pData);
        }
        else
        {
            delete pDbl;
        }

        Scierror(999, _("%s: LAPACK error n°%d.\n"), fname, iRet);
        return Function::Error;
    }

    if (bIsComplex)
    {
        vFreeDoubleComplexFromPointer((doublecomplex*)pData);
    }
    else
    {
        delete pDbl;
    }

    if (_iRetCount == 2)
    {
        out.push_back(new Double((double)iExponent));
    }

    out.push_back(pDblMantissa);
    return Function::OK;
}
