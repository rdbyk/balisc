/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Cedric Delamarre
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
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

#include "prod.hxx"

extern "C"
{
#include "matrix_multiplication.h"
#if defined(__SSE2__)
#include "emmintrin.h"
#endif
}

types::Double* prod(types::Double* pIn, int iOrientation)
{
    types::Double* pOut = NULL;
    double* pdblInReal  = pIn->getReal();
    double* pdblInImg   = pIn->getImg();

    if (iOrientation == 0) // all
    {
        if (pIn->isComplex())
        {
            double dblR = pdblInReal[0];
            double dblI = pdblInImg[0];
            double dblRTmp = 0;
            double dblITmp = 0;
            for (int i = 1; i < pIn->getSize(); i++)
            {
                dblRTmp = dblR * pdblInReal[i] - dblI * pdblInImg[i];
                dblITmp = dblR * pdblInImg[i] + dblI * pdblInReal[i];

                dblR = dblRTmp;
                dblI = dblITmp;
            }

            pOut = new types::Double(dblR, dblI);
        }
        else
        {
#if !defined(__SSE2__)
            double dblR = pdblInReal[0];
            
            for (int i = 1; i < pIn->getSize(); i++)
            {
                dblR *= pdblInReal[i];
            }

            pOut = new types::Double(dblR);
#else
            int imax = pIn->getSize() - 1;
            
            __m128d s = _mm_set1_pd(1);
            
            for (int i = 0 ; i < imax ; i += 2)
            {
                s = _mm_mul_pd(s, *((__m128d*)(&(pdblInReal[i]))));
            }
            if (pIn->getSize() % 2)
            {
                pOut = new types::Double(s[0] * s[1] * pdblInReal[imax]);
            }
            else
            {
                pOut = new types::Double(s[0] * s[1]);
            }
#endif
        }
    }
    else // prod on one dimension
    {
        // create output dimensions
        int iDims   = pIn->getDims();
        int* piDims = new int[iDims];

        for (int i = 0 ; i < iDims ; i++)
        {
            piDims[i] = pIn->getDimsArray()[i];
        }

        piDims[iOrientation - 1] = 1;

        // create output variable
        pOut = new types::Double(iDims, piDims, pIn->isComplex());
        delete[] piDims;
        piDims = NULL;

        // init output
        double* pdblOut = pOut->get();
        double* pdblOutImg = pOut->getImg();
        int size = pOut->getSize();

        if (pOut->isComplex())
        {
            for (int i = 0; i < size; i++)
            {
                pdblOut[i] = 1;
                pdblOutImg[i] = 0;
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                pdblOut[i] = 1;
            }
        }

        // perform operations
        int* piIndex = new int[iDims];
        size = pIn->getSize();
        if (pIn->isComplex())
        {
            for (int i = 0; i < size; i++)
            {
                //get array of dim
                pIn->getIndexes(i, piIndex);

                //convert indexes for result
                piIndex[iOrientation - 1] = 0;
                int iIndex = pOut->getIndex(piIndex);

                double dblRTmp = pdblOut[iIndex];
                double dblITmp = pdblOutImg[iIndex];

                iMultiComplexMatrixByComplexMatrix( &pdblInReal[i], &pdblInImg[i], 1, 1,
                                                    &dblRTmp, &dblITmp, 1, 1,
                                                    &pdblOut[iIndex], &pdblOutImg[iIndex]);
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                //get array of dim
                pIn->getIndexes(i, piIndex);

                //convert indexes for result
                piIndex[iOrientation - 1] = 0;
                int iIndex = pOut->getIndex(piIndex);
                pdblOut[iIndex] *= pdblInReal[i];
            }
        }

        delete[] piIndex;
        piIndex = NULL;
    }

    return pOut;
}

// polynom
types::Polynom* prod(types::Polynom* pIn, int iOrientation)
{
    types::Polynom* pOut = NULL;
    if (iOrientation == 0) // sum of all element
    {
        // get rank of all input single poly
        int* piRanks = new int[pIn->getSize()];
        pIn->getRank(piRanks);

        // compute the output rank
        int iRankMax = 0;
        for (int i = 0; i < pIn->getSize(); i++)
        {
            iRankMax += piRanks[i];
        }

        // create output matrix of poly
        pOut = new types::Polynom(pIn->getVariableName(), 1, 1, &iRankMax);
        pOut->setComplex(pIn->isComplex());
        double* pdblRealOut = pOut->getScalar_()->get();
        memcpy(pdblRealOut, pIn->getScalar_()->get(), (piRanks[0] + 1) * sizeof(double));

        // do prod
        int iSize = pIn->getSize();
        double* pdblTempReal = new double[iRankMax + 1];
        int iRank = piRanks[0];
        if (pIn->isComplex())
        {
            double* pdblImgOut = pOut->getScalar_()->getImg();
            // alloc temporary workspace
            double* pdblTempImg  = new double[iRankMax + 1];
            memcpy(pdblImgOut, pIn->getScalar_()->getImg(), (piRanks[0] + 1) * sizeof(double));

            // perform operations
            for (int i = 1; i < iSize; i++)
            {
                double* pdblRealIn = pIn->get_(i)->get();
                double* pdblImgIn = pIn->get_(i)->getImg();
                memcpy(pdblTempReal, pdblRealOut, (iRank + 1) * sizeof(double));
                memcpy(pdblTempImg,  pdblImgOut,  (iRank + 1) * sizeof(double));
                iMultiComplexPolyByComplexPoly(pdblTempReal, pdblTempImg, iRank + 1,
                                               pdblRealIn, pdblImgIn, piRanks[i] + 1,
                                               pdblRealOut, pdblImgOut, iRankMax + 1);
                iRank += piRanks[i];
            }

            delete[] pdblTempImg;
        }
        else
        {
            // perform operations
            for (int i = 1; i < iSize; i++)
            {
                double* pdblRealIn = pIn->get_(i)->get();
                memcpy(pdblTempReal, pdblRealOut, (iRank + 1) * sizeof(double));
                iMultiScilabPolynomByScilabPolynom(pdblTempReal, iRank + 1,
                                                   pdblRealIn, piRanks[i] + 1,
                                                   pdblRealOut, iRankMax + 1);
                iRank += piRanks[i];
            }
        }

        delete[] pdblTempReal;
        delete[] piRanks;
    }
    else // sum following a dimension
    {
        // create output dimensions
        int iDims = pIn->getDims();
        int* piDims = new int[iDims];

        for (int i = 0 ; i < iDims ; i++)
        {
            piDims[i] = pIn->getDimsArray()[i];
        }

        piDims[iOrientation - 1] = 1;

        // get input ranks in int*
        int* piRanks = new int[pIn->getSize()];
        pIn->getRank(piRanks);

        // get input ranks in types::Double
        types::Double* pDblRanks = new types::Double(pIn->getDims(), pIn->getDimsArray());
        for (int i = 0; i < pDblRanks->getSize(); i++)
        {
            pDblRanks->set_(i, static_cast<double>(piRanks[i]));
        }

        // create output max ranks
        types::Double* pDblRanksOut = new types::Double(iDims, piDims);
        double* pdblOut = pDblRanksOut->get();
        for (int i = 0; i < pDblRanksOut->getSize(); i++)
        {
            pdblOut[i] = 0;
        }

        // compute the maximum ranks for the dim n
        int*    piIndex = new int[iDims];
        double* pdblIn  = pDblRanks->get();
        for (int i = 0 ; i < pDblRanks->getSize() ; i++)
        {
            //get array of dim
            pDblRanks->getIndexes(i, piIndex);

            //convert indexes for result
            piIndex[iOrientation - 1] = 0;
            int iIndex = pDblRanksOut->getIndex(piIndex);
            pdblOut[iIndex] += pdblIn[i];
        }
        pDblRanks->killMe();

        // move output ranks from types::Double to int*
        int* piRankMax = new int[pDblRanksOut->getSize()];
        int* piRankTmp = new int[pDblRanksOut->getSize()];
        int iMaxOutputRank = 0;
        for (int i = 0; i < pDblRanksOut->getSize(); i++)
        {
            piRankMax[i] = static_cast<int>(pdblOut[i]);
            iMaxOutputRank = std::max(iMaxOutputRank, piRankMax[i]);
        }

        pDblRanksOut->killMe();
        // create the outpout polynom
        pOut = new types::Polynom(pIn->getVariableName(), iDims, piDims, piRankMax);
        pOut->setComplex(pIn->isComplex());

        // init output with first element of lead dimension
        if (pIn->isComplex())
        {

            for (int i = 0; i < pOut->getSize(); i++)
            {
                pOut->getIndexes(i, piIndex);
                int iIndex = pIn->getIndex(piIndex);
                memcpy(pOut->get_(i)->get(), pIn->get_(iIndex)->get(), (piRanks[iIndex] + 1) * sizeof(double));
                memcpy(pOut->get_(i)->getImg(), pIn->get_(iIndex)->getImg(), (piRanks[iIndex] + 1) * sizeof(double));
                piRankTmp[i] = piRanks[iIndex];
            }
        }
        else
        {
            for (int i = 0; i < pOut->getSize(); i++)
            {
                pOut->getIndexes(i, piIndex);
                int iIndex = pIn->getIndex(piIndex);
                memcpy(pOut->get_(i)->get(), pIn->get_(iIndex)->get(), (piRanks[iIndex] + 1) * sizeof(double));
                piRankTmp[i] = piRanks[iIndex];
            }
        }

        // alloc temporary workspace
        double* pdblTempReal = new double[iMaxOutputRank + 1];
        if (pIn->isComplex())
        {
            // alloc temporary workspace
            double* pdblTempImg  = new double[iMaxOutputRank + 1];

            // perform operations
            for (int i = 0 ; i < pIn->getSize() ; i++)
            {
                //get array of dim
                pIn->getIndexes(i, piIndex);

                //convert indexes for result
                if (piIndex[iOrientation - 1] == 0)
                {
                    // first element of lead dimension is already setted.
                    continue;
                }

                piIndex[iOrientation - 1] = 0;
                int iIndex = pOut->getIndex(piIndex);

                // make sum on each ranks
                double* pdblRealIn = pIn->get_(i)->get();
                double* pdblRealOut = pOut->get_(iIndex)->get();
                double* pdblImgIn = pIn->get_(i)->getImg();
                double* pdblImgOut = pOut->get_(iIndex)->getImg();
                memcpy(pdblTempReal, pdblRealOut, (piRankTmp[iIndex] + 1) * sizeof(double));
                memcpy(pdblTempImg,  pdblImgOut,  (piRankTmp[iIndex] + 1) * sizeof(double));
                iMultiComplexPolyByComplexPoly(pdblTempReal, pdblTempImg, piRankTmp[iIndex] + 1,
                                               pdblRealIn, pdblImgIn, piRanks[i] + 1,
                                               pdblRealOut, pdblImgOut, piRankMax[iIndex] + 1);
                piRankTmp[iIndex] += piRanks[i];
            }

            delete[] pdblTempImg;
        }
        else
        {
            // perform operations
            for (int i = 0 ; i < pIn->getSize() ; i++)
            {
                //get array of dim
                pIn->getIndexes(i, piIndex);

                //convert indexes for result
                if (piIndex[iOrientation - 1] == 0)
                {
                    // first element of lead dimension is already setted.
                    continue;
                }

                piIndex[iOrientation - 1] = 0;
                int iIndex = pOut->getIndex(piIndex);

                // make sum on each ranks
                double* pdblRealIn = pIn->get_(i)->get();
                double* pdblRealOut = pOut->get_(iIndex)->get();
                memcpy(pdblTempReal, pdblRealOut, (piRankTmp[iIndex] + 1) * sizeof(double));
                iMultiScilabPolynomByScilabPolynom(pdblTempReal, piRankTmp[iIndex] + 1,
                                                   pdblRealIn, piRanks[i] + 1,
                                                   pdblRealOut, piRankMax[iIndex] + 1);
                piRankTmp[iIndex] += piRanks[i];
            }
        }

        delete[] pdblTempReal;
        delete[] piRankMax;
        delete[] piRanks;
        delete[] piIndex;
        delete[] piDims;
        delete[] piRankTmp;
    }

    pOut->updateRank();
    return pOut;
}

