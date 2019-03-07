/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Bernard HUGUENEY
 * Copyright (C) 2011 - DIGITEO - Cedric DELAMARRE
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
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
#include "qr.h"
#include "doublecomplex.h"
#include "sci_malloc.h"
}

types::Function::ReturnValue sci_qr(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::Double* pDbl     = NULL;
    types::Double* pDblQ    = NULL;
    types::Double* pDblR    = NULL;
    types::Double* pDblE    = NULL;
    types::Double* pDblRk   = NULL;
    double* pdQ             = NULL;
    double* pdR             = NULL;
    double* pData           = NULL;
    double dTol             = -1.;
    int iRowsToCompute      = 0;

    if (in.size() != 1 && in.size() != 2)
    {
        Scierror(72, 1, 2);
        return types::Function::Error;
    }

    if (_iRetCount > 4)
    {
        Scierror(82, 1, 4);
        return types::Function::Error;
    }

    if ((in[0]->isDouble() == false))
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_qr";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    pDbl = in[0]->getAs<types::Double>();

    if ((pDbl->getCols() == 0) || (pDbl->getRows() == 0))
    {
        if (_iRetCount == 4)
        {
            types::Double* zero = new types::Double(1, 1);
            zero->set(0, 0);
            out.push_back(types::Double::Empty());
            out.push_back(types::Double::Empty());
            out.push_back(zero);
            out.push_back(types::Double::Empty());
        }
        else
        {
            out.push_back(types::Double::Empty());
            for (int i = 1; i < _iRetCount; i++)
            {
                out.push_back(types::Double::Empty());
            }
        }
        return types::Function::OK;
    }

    if ((pDbl->getRows() == -1) || (pDbl->getCols() == -1)) // manage eye case
    {
        Scierror(271, _("%s: Size varying argument a*eye(), (arg %d) not allowed here.\n"), "qr", 1);
        return types::Function::Error;
    }

    iRowsToCompute = pDbl->getRows();

    if (in.size() == 2)
    {
        if (in[1]->isString() == true)
        {
            /* /!\ original code did not check that string is "e" so any [matrix of] string is accepted as "e" ! */
            /*
            types::String* pStr = in[1]->getAs<types::String>();
            if((wcslen(pStr->getFirst()) == 1) && (pStr->getFirst()[0] == L'e'))
            */

            if (_iRetCount == 4)
            {
                Scierror(93, 2);
                return types::Function::Error;
            }

            iRowsToCompute = std::min(pDbl->getRows(), pDbl->getCols());
        }
        else if (in[1]->isDouble() == true)
        {
            /* /!\ original code do not check anything (real && 1x1 matrix)*/
            dTol = in[1]->getAs<types::Double>()->getFirst();
        }
        else
        {
            Scierror(90, 2, _("real scalar or string"));
            return types::Function::Error;
        }
    }

    pDbl = pDbl->clone()->getAs<types::Double>();

    if (pDbl->isComplex())
    {
        // this allocates memory!
        pData = (double*)oGetDoubleComplexFromPointer(pDbl->getReal(), pDbl->getImg(), pDbl->getSize());
        if (!pData)
        {
            Scierror(1);
            vFreeDoubleComplexFromPointer((doublecomplex*)pData);
            return types::Function::Error;
        }
    }
    else
    {
        pData = pDbl->getReal();
    }

    pDblQ = new types::Double(pDbl->getRows(), iRowsToCompute, pDbl->isComplex());
    pDblR = new types::Double(iRowsToCompute, pDbl->getCols(), pDbl->isComplex());

    if (pDbl->isComplex())
    {
        pdQ = (double*) MALLOC(pDbl->getRows() * iRowsToCompute * sizeof(doublecomplex));
        pdR = (double*) MALLOC(iRowsToCompute * pDbl->getCols() * sizeof(doublecomplex));
    }
    else
    {
        pdQ = pDblQ->get();
        pdR = pDblR->get();
    }

    if (_iRetCount >= 3) /* next alloc for E needed only for _iRetCount>=3 */
    {
        pDblE = new types::Double(pDbl->getCols(), pDbl->getCols());
    }

    if (_iRetCount >= 4) /* next alloc for Rk needed only for _iRetCount>=4 */
    {
        pDblRk = new types::Double(1, 1);
    }

    int iRet = iQrM(pData, pDbl->getRows(), pDbl->getCols(), pDbl->isComplex(), iRowsToCompute, dTol, pdQ, pdR, (pDblE ? pDblE->get() : NULL), (pDblRk ? pDblRk->get() : NULL));

    if (iRet != 0)
    {
        Scierror(180, iRet);

        if (pDbl->isComplex())
        {
            FREE(pdR);
            FREE(pdQ);
            vFreeDoubleComplexFromPointer((doublecomplex*)pData);
        }

        if (_iRetCount >= 3)
        {
            delete pDblE;
        }

        if (_iRetCount >= 4)
        {
            delete pDblRk;
        }

        delete pDblR;
        delete pDblQ;
        delete pDbl; // because of cloning, cf. above

        return types::Function::Error;
    }

    if (pDbl->isComplex())
    {
        vGetPointerFromDoubleComplex((doublecomplex*)pdQ, pDblQ->getSize(), pDblQ->getReal(), pDblQ->getImg());
        vFreeDoubleComplexFromPointer((doublecomplex*)pdQ);
        vGetPointerFromDoubleComplex((doublecomplex*)pdR, pDblR->getSize(), pDblR->getReal(), pDblR->getImg());
        vFreeDoubleComplexFromPointer((doublecomplex*)pdR);
        vFreeDoubleComplexFromPointer((doublecomplex*)pData);
    }

    delete pDbl; // because of cloning, cf. above

    out.push_back(pDblQ);

    if (_iRetCount >= 2)
    {
        out.push_back(pDblR);
    }

    if (_iRetCount == 3)
    {
        out.push_back(pDblE);
    }
    else if (_iRetCount == 4)
    {
        out.push_back(pDblRk);
        out.push_back(pDblE);
    }

    return types::Function::OK;
}
