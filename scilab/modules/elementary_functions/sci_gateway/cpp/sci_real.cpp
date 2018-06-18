/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
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

#include "elem_func_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "overload.hxx"
#include "sparse.hxx"
#include "polynom.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "elem_common.h"
}

using types::Double;
using types::Function;
using types::Polynom;
using types::Sparse;
using types::typed_list;

Function::ReturnValue sci_real(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d expected.\n"), "real", 1);
        return Function::Error;
    }

    if (in[0]->isDouble())
    {
        Double* pDblIn = in[0]->getAs<Double>();

        if (pDblIn->isComplex())
        {
            if (pDblIn->getRef() > 1)
            {
                Double* pDblOut = new Double(pDblIn->getDims(), pDblIn->getDimsArray());
                memcpy(pDblOut->get(), pDblIn->get(), pDblIn->getSize() * sizeof(double));
                out.push_back(pDblOut);
            }
            else
            {
                pDblIn->setComplex(false);
                out.push_back(pDblIn);
            }
        }
        else
        {
            out.push_back(pDblIn);
        }

        return Function::OK;
    }
    else if (in[0]->isSparse())
    {
        Sparse* pSparseIn = in[0]->getAs<Sparse>();
        if (pSparseIn->isComplex() == false)
        {
            out.push_back(pSparseIn);
            return Function::OK;
        }

        Sparse* pSparseOut = new Sparse(pSparseIn->getRows(), pSparseIn->getCols());
        int const nonZeros = static_cast<int>(pSparseIn->nonZeros());
        int* pRows = new int[nonZeros * 2];
        pSparseIn->outputRowCol(pRows);
        int* pCols = pRows + nonZeros;

        for (int i = 0 ; i < nonZeros ; i++)
        {
            double real = pSparseIn->getReal(pRows[i] - 1, pCols[i] - 1);
            pSparseOut->set(pRows[i] - 1, pCols[i] - 1, real, false);
        }

        pSparseOut->finalize();

        delete[] pRows;

        out.push_back(pSparseOut);
    }
    else if (in[0]->isPoly())
    {
        Polynom* pPolyIn = in[0]->getAs<Polynom>();
        if (pPolyIn->isComplex() == false)
        {
            out.push_back(pPolyIn);
            return Function::OK;
        }

        int* piRanks = new int[pPolyIn->getSize()];
        pPolyIn->getRank(piRanks);

        Polynom* pPolyOut = new Polynom(pPolyIn->getVariableName(), pPolyIn->getDims(), pPolyIn->getDimsArray(), piRanks);
        for (int i = 0; i < pPolyIn->getSize(); i++)
        {
            memcpy(pPolyOut->get(i)->get(), pPolyIn->get(i)->get(), (piRanks[i] + 1) * sizeof(double));
        }

        delete[] piRanks;
        pPolyOut->updateRank();
        out.push_back(pPolyOut);
    }
    else
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_real";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    return Function::OK;
}
