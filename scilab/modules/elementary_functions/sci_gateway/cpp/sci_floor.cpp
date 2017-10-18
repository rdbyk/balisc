/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - DIGITEO - Cedric DELAMARRE
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyrigth (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 * 
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */
/*--------------------------------------------------------------------------*/
#include "elem_func_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "overload.hxx"
#include "sparse.hxx"
#include "polynom.hxx"

#include "floor.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}
/*
clear a; nb = 2500; a = rand(nb, nb); tic(); floor(a); toc
clear a; nb = 2500; a = rand(nb, nb); a = a + a *%i; tic(); floor(a); toc
*/
/*--------------------------------------------------------------------------*/
types::Function::ReturnValue sci_floor(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), "floor", 1);
        return types::Function::Error;
    }

    if (_iRetCount > 1)
    {
        Scierror(78, _("%s: Wrong number of output argument(s): %d expected.\n"), "floor", 1);
        return types::Function::Error;
    }

    if (in[0]->isDouble())
    {
        out.push_back(balisc::floor(in[0]->getAs<types::Double>()));
        return types::Function::OK;
    }
    else if (in[0]->isSparse())
    {
        types::Sparse* pSparseIn = in[0]->getAs<types::Sparse>();
        types::Sparse* pSparseOut = new types::Sparse(pSparseIn->getRows(), pSparseIn->getCols(), pSparseIn->isComplex());

        int const nonZeros = static_cast<int>(pSparseIn->nonZeros());
        int* pRows = new int[nonZeros * 2];
        pSparseIn->outputRowCol(pRows);
        int* pCols = pRows + nonZeros;

        double* pNonZeroR = new double[nonZeros];
        double* pNonZeroI = new double[nonZeros];
        pSparseIn->outputValues(pNonZeroR, pNonZeroI);

        if (pSparseIn->isComplex())
        {
            for (int i = 0; i < nonZeros; i++)
            {
                std::complex<double> cplx(std::floor(pNonZeroR[i]), std::floor(pNonZeroI[i]));
                pSparseOut->set(pRows[i] - 1, pCols[i] - 1, cplx, false);
            }
        }
        else
        {
            for (int i = 0; i < nonZeros; i++)
            {
                pSparseOut->set(pRows[i] - 1, pCols[i] - 1, std::floor(pNonZeroR[i]), false);
            }
        }

        pSparseOut->finalize();

        delete[] pRows;
        delete[] pNonZeroR;
        delete[] pNonZeroI;

        out.push_back(pSparseOut);
        return types::Function::OK;
    }
    else if (in[0]->isPoly())
    {
        types::Polynom* pPolyIn = in[0]->getAs<types::Polynom>();
        types::Polynom* pPolyOut = new types::Polynom(pPolyIn->getVariableName(), pPolyIn->getDims(), pPolyIn->getDimsArray());

        double* dataImg  = NULL;
        double* dataReal = NULL;

        if (pPolyIn->isComplex())
        {
            for (int i = 0; i < pPolyIn->getSize(); i++)
            {
                int rank = pPolyIn->get_(i)->getRank();
                types::SinglePoly* pSP = new types::SinglePoly(&dataReal, &dataImg, rank);

                for (int j = 0; j < rank + 1; j++)
                {
                    dataReal[j] = std::floor(pPolyIn->get_(i)->get()[j]);
                    dataImg[j]  = std::floor(pPolyIn->get_(i)->getImg()[j]);
                }

                pPolyOut->set_(i, pSP);
                delete pSP;
                pSP = NULL;
            }
        }
        else
        {
            for (int i = 0; i < pPolyIn->getSize(); i++)
            {
                int rank = pPolyIn->get_(i)->getRank();
                types::SinglePoly* pSP = new types::SinglePoly(&dataReal, rank);

                for (int j = 0; j < rank + 1; j++)
                {
                    dataReal[j] = std::floor(pPolyIn->get_(i)->get()[j]);
                }

                pPolyOut->set_(i, pSP);
                delete pSP;
                pSP = NULL;
            }
        }

        out.push_back(pPolyOut);
        return types::Function::OK;
    }
    else if (in[0]->isInt())
    {
        out.push_back(in[0]);
        return types::Function::OK;
    }
    else
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_floor";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }
}
/*--------------------------------------------------------------------------*/
