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
#include "clean.hxx"
#include "sparse.hxx"
#include "polynom.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Double;
using types::Function;
using types::Polynom;
using types::SinglePoly;
using types::Sparse;
using types::typed_list;

static const char fname[] = "clean";

Function::ReturnValue sci_clean(typed_list &in, int _iRetCount, typed_list &out)
{
    Double* pDblOut      = NULL;
    Polynom* pPolyOut    = NULL;
    Sparse* pSparseOut   = NULL;

    double* pdReal  = NULL;
    double* pdImg   = NULL;

    double dEpsR    = 1E-10;
    double dEpsA    = 1E-10;

    int iSize       = 0;

    //Only for Sparse case
    int* pRows = NULL;
    int* pCols = NULL;

    if (in.size() < 1 || in.size() > 3)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d to %d expected.\n"), fname, 1, 3);
        return Function::Error;
    }

    /***** get data *****/
    if (in[0]->isDouble())
    {
        pDblOut = in[0]->getRef() > 1 ? in[0]->getAs<Double>()->clone()->getAs<Double>() : in[0]->getAs<Double>();

        iSize = pDblOut->getSize();
        pdReal = pDblOut->get();
        if (pDblOut->isComplex())
        {
            pdImg = pDblOut->getImg();
        }
    }
    else if (in[0]->isPoly())
    {
        Polynom* pPolyIn = in[0]->getAs<Polynom>();
        iSize = pPolyIn->getSize();
        pPolyOut = pPolyIn->clone()->getAs<Polynom>();
    }
    else if (in[0]->isSparse())
    {
        Sparse* pSparseIn = in[0]->getAs<Sparse>();
        pSparseOut = new Sparse(pSparseIn->getRows(), pSparseIn->getCols());

        iSize = static_cast<int>(pSparseIn->nonZeros());
        pRows = new int[iSize * 2];
        pSparseIn->outputRowCol(pRows);
        pCols = pRows + iSize;

        pdReal = new double[iSize];
        if (pSparseIn->isComplex())
        {
            pdImg  = new double[iSize];
        }

        pSparseIn->outputValues(pdReal, pdImg);
    }
    else
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_clean";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }


    if (in.size() == 3)
    {
        if (in[2]->isDouble() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d : A real scalar expected.\n"), fname, 3);
            if (in[0]->isSparse())
            {
                delete pSparseOut;
                delete[] pdReal;
                delete[] pRows;
                if (pdImg)
                {
                    delete[] pdImg;
                }
            }
            return Function::Error;
        }

        Double* pDbl = in[2]->getAs<Double>();

        if (pDbl->isScalar() == false || pDbl->isComplex())
        {
            Scierror(999, _("%s: Wrong type for input argument #%d : A real scalar expected.\n"), fname, 3);
            if (in[0]->isSparse())
            {
                delete pSparseOut;
                delete[] pdReal;
                delete[] pRows;
                if (pdImg)
                {
                    delete[] pdImg;
                }
            }
            return Function::Error;
        }

        dEpsR = pDbl->getFirst();
    }

    if (in.size() >= 2)
    {
        if (in[1]->isDouble() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d : A real scalar expected.\n"), fname, 2);
            if (in[0]->isSparse())
            {
                delete pSparseOut;
                delete[] pdReal;
                delete[] pRows;
                if (pdImg)
                {
                    delete[] pdImg;
                }
            }
            return Function::Error;
        }

        Double* pDbl = in[1]->getAs<Double>();

        if (pDbl->isScalar() == false || pDbl->isComplex())
        {
            Scierror(999, _("%s: Wrong type for input argument #%d : A real scalar expected.\n"), fname, 2);
            if (in[0]->isSparse())
            {
                delete pSparseOut;
                delete[] pdReal;
                delete[] pRows;
                if (pdImg)
                {
                    delete[] pdImg;
                }
            }
            return Function::Error;
        }

        dEpsA = pDbl->getFirst();
    }

    /***** perform operation *****/
    if (in[0]->isPoly())
    {
        for (int i = 0 ; i < iSize ; i++)
        {
            SinglePoly* pSP = pPolyOut->get(i);
            clean(pSP->get(), pSP->getImg(), pSP->getSize(), dEpsA, dEpsR);
        }
    }
    else
    {
        clean(pdReal, pdImg, iSize, dEpsA, dEpsR);
    }

    /***** set result *****/
    if (in[0]->isDouble())
    {
        out.push_back(pDblOut);
    }
    else if (in[0]->isPoly())
    {
        pPolyOut->updateRank();
        out.push_back(pPolyOut);
    }
    else if (in[0]->isSparse())
    {
        if (pdImg)
        {
            for (int i = 0 ; i < iSize ; i++)
            {
                std::complex<double> cplx = std::complex<double>(pdReal[i], pdImg[i]);
                pSparseOut->set(pRows[i] - 1, pCols[i] - 1, cplx, false);
            }

            delete[] pdImg;
        }
        else
        {
            for (int i = 0 ; i < iSize ; i++)
            {
                pSparseOut->set(pRows[i] - 1, pCols[i] - 1, pdReal[i], false);
            }
        }

        pSparseOut->finalize();

        delete[] pdReal;
        delete[] pRows;
        out.push_back(pSparseOut);
    }

    return Function::OK;
}
