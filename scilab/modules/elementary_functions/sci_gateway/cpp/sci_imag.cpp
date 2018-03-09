/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - DIGITEO - Cedric DELAMARRE
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

#include <complex>
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
using types::SinglePoly;
using types::Sparse;
using types::typed_list;

Function::ReturnValue sci_imag(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), "imag", 1);
        return Function::Error;
    }

    if (in[0]->isDouble())
    {
        Double* pDblIn = in[0]->getAs<Double>();
        Double* pDblOut = pDblIn->getRef() > 1 ? new Double(pDblIn->getDims(), pDblIn->getDimsArray()) : pDblIn;

        if (pDblIn->isComplex())
        {
            memcpy(pDblOut->get(), pDblIn->getImg(), pDblIn->getSize() * sizeof(double));
            pDblOut->setComplex(false);
        }
        else
        {
            memset(pDblOut->get(), 0x00, pDblIn->getSize() * sizeof(double));
        }


        out.push_back(pDblOut);
    }
    else if (in[0]->isSparse())
    {
        Sparse* pSparseIn = in[0]->getAs<Sparse>();
        Sparse* pSparseOut = new Sparse(pSparseIn->getRows(), pSparseIn->getCols());

        if (pSparseIn->isComplex() == false)
        {
            out.push_back(pSparseOut);
            return Function::OK;
        }

        int const nonZeros = static_cast<int>(pSparseIn->nonZeros());
        int* pRows = new int[nonZeros * 2];
        pSparseIn->outputRowCol(pRows);
        int* pCols = pRows + nonZeros;

        for (int i = 0 ; i < nonZeros ; i++)
        {
            std::complex<double> cplx = pSparseIn->getImg(pRows[i] - 1, pCols[i] - 1);
            pSparseOut->set(pRows[i] - 1, pCols[i] - 1, cplx.imag(), false);
        }

        pSparseOut->finalize();

        delete[] pRows;

        out.push_back(pSparseOut);
    }
    else if (in[0]->isPoly())
    {
        Polynom* pPolyIn  = in[0]->getAs<Polynom>();
        Polynom* pPolyOut = NULL;

        if (pPolyIn->isComplex())
        {
            pPolyOut = new Polynom(pPolyIn->getVariableName(), pPolyIn->getDims(), pPolyIn->getDimsArray());
            for (int i = 0; i < pPolyIn->getSize(); i++)
            {
                int rank = pPolyIn->get(i)->getRank();
                int iNewRank = rank;

                // Reduce the rank of output polynom if the last ranks are null
                for (int j = rank ; j > 0 ; j--)
                {
                    if (pPolyIn->get(i)->getImg()[j] == 0.0)
                    {
                        iNewRank--;
                    }
                    else
                    {
                        break;
                    }
                }

                double* dataReal = NULL;
                SinglePoly* pSP = new SinglePoly(&dataReal, iNewRank);

                for (int j = 0; j < iNewRank + 1; j++)
                {
                    dataReal[j] = pPolyIn->get(i)->getImg()[j];
                }

                pPolyOut->set(i, pSP);
                delete pSP;
                pSP = NULL;
            }
        }
        else
        {
            int iSize = pPolyIn->getSize();
            int* piRanks = new int[iSize];
            memset(piRanks, 0x00, iSize * sizeof(int));
            pPolyOut = new Polynom(pPolyIn->getVariableName(), pPolyIn->getDims(), pPolyIn->getDimsArray(), piRanks);
            pPolyOut->setZeros();
            delete[] piRanks;
        }

        out.push_back(pPolyOut);
    }
    else
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_imag";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    return Function::OK;
}
