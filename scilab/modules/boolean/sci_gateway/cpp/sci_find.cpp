/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - DIGITEO - Antoine ELIAS
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

#include "boolean_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "string.hxx"
#include "bool.hxx"
#include "sparse.hxx"
#include "overload.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
}

using types::Bool;
using types::Double;
using types::Function;
using types::GenericType;
using types::Sparse;
using types::SparseBool;
using types::typed_list;

static void getCoordFromIndex(int _iIndex, int* _piIndexes, int* _piDims, int _iDims);

Function::ReturnValue sci_find(typed_list &in, int _iRetCount, typed_list &out)
{
    int iMax = -1;
    int iRetCount = std::max(1, _iRetCount);

    if (in.size() == 0 || in.size() > 2)
    {
        Scierror(72, 1, 2);
        return Function::Error;
    }

    if (in.size() == 2)
    {
        if (in[1]->isDouble() == false || in[1]->getAs<Double>()->isScalar() == false)
        {
            Scierror(90, 2, _("positive integer value"));
            return Function::Error;
        }

        iMax = (int)in[1]->getAs<Double>()->get()[0];
        if (iMax <= 0 && iMax != -1)
        {
            Scierror(110, 2, _("positive integer value"));
            return Function::Error;
        }

    }

    int* piIndex = 0;
    int iValues = 0;

    if (in[0]->isGenericType() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_find";
        return Overload::call(wstFuncName, in, iRetCount, out);
    }

    GenericType* pGT = in[0]->getAs<GenericType>();
    piIndex = new int[pGT->getSize()];

    if (in[0]->isBool())
    {
        Bool* pB = in[0]->getAs<Bool>();
        int size = pB->getSize();
        int* p = pB->get();

        if (iMax < 0)
        {
            for (int i = 0; i < size; i++)
            {
                if (p[i])
                {
                    piIndex[iValues++] = i;
                }
            }
        }
        else
        {
            iMax = std::min(iMax, size);

            for (int i = 0; i < size; i++)
            {
                if (p[i])
                {
                    piIndex[iValues++] = i;
                    if (iValues >= iMax)
                    {
                        break;
                    }
                }
            }
        }
    }
    else if (in[0]->isDouble())
    {
        Double* pD = in[0]->getAs<Double>();
        int size = pD->getSize();
        double* p = pD->get();
        iMax = iMax == -1 ? size : std::min(iMax, size);
        for (int i = 0; i < size && iValues < iMax; i++)
        {
            if (p[i])
            {
                piIndex[iValues] = i;
                iValues++;
            }
        }
    }
    else if (in[0]->isSparse())
    {
        Sparse* pSP = in[0]->getAs<Sparse>();
        int iNNZ = (int)pSP->nonZeros();
        int iRows = pSP->getRows();
        int* pRows = new int[iNNZ * 2];
        pSP->outputRowCol(pRows);
        int *pCols = pRows + iNNZ;
        iMax = iMax == -1 ? iNNZ : std::min(iMax, iNNZ);

        for (int i = 0; i < iNNZ && iValues < iMax; i++)
        {
            piIndex[iValues] = (pCols[i] - 1) * iRows + (pRows[i] - 1);
            iValues++;
        }

        delete[] pRows;
    }
    else if (in[0]->isSparseBool())
    {
        SparseBool* pSB = in[0]->getAs<SparseBool>();
        int iNNZ = (int)pSB->nbTrue();
        int iRows = pSB->getRows();

        int* pRows = new int[iNNZ * 2];
        pSB->outputRowCol(pRows);
        int* pCols = pRows + iNNZ;

        iMax = iMax == -1 ? iNNZ : std::min(iMax, iNNZ);
        for (int i = 0; i < iNNZ && iValues < iMax; i++)
        {
            piIndex[iValues] = (pCols[i] - 1) * iRows + (pRows[i] - 1);
            iValues++;
        }

        delete[] pRows;
    }
    else
    {
        delete[] piIndex;

        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_find";
        return Overload::call(wstFuncName, in, iRetCount, out);
    }

    if (iValues == 0)
    {
        for (int i = 0 ; i < iRetCount ; i++)
        {
            out.push_back(Double::Empty());
        }
    }
    else
    {
        if (iRetCount <= 1)
        {
            Double* dbl = new Double(1, iValues);
            double* p = dbl->get();

            for (int i = 0; i < iValues; ++i)
            {
                p[i] = static_cast<double>(piIndex[i]) + 1;
            }

            delete[] piIndex;
            out.push_back(dbl);
            return Function::OK;
        }

        int* piRefDims = pGT->getDimsArray();
        int iRefDims = pGT->getDims();

        int* piDims = new int[iRetCount];
        int iDims = iRetCount;

        if (iDims == iRefDims)
        {
            for (int i = 0 ; i < iRefDims ; i++)
            {
                piDims[i] = piRefDims[i];
            }
        }
        else if (iDims > iRefDims)
        {
            int i = 0;
            for ( ; i < iRefDims ; i++)
            {
                piDims[i] = piRefDims[i];
            }

            for ( ; i < iDims ; i++)
            {
                piDims[i] = 1;
            }
        }
        else //iDims < iRefDims
        {
            int iDimsMinusOne = iDims - 1;

            int i = 0;
            for ( ; i < iDimsMinusOne ; i++)
            {
                piDims[i] = piRefDims[i];
            }

            piDims[iDimsMinusOne] = 1;

            for ( ; i < iRefDims ; i++)
            {
                piDims[iDimsMinusOne] *= piRefDims[i];
            }
        }

        int** piCoord = new int*[iValues];
        for (int i = 0 ; i < iValues ; i++)
        {
            piCoord[i] = new int[iRetCount];
            getCoordFromIndex(piIndex[i], piCoord[i], piDims, iDims);
        }

        for (int i = 0 ; i < iRetCount ; i++)
        {
            Double* pOut = new Double(1, iValues);
            double* pd = pOut->get();
            for (int j = 0 ; j < iValues ; j++)
            {
                pd[j] = piCoord[j][i] + 1;
            }
            out.push_back(pOut);
        }

        delete[] piDims;
        for (int i = 0 ; i < iValues ; i++)
        {
            delete[] piCoord[i];
        }
        delete[] piCoord;
    }

    delete[] piIndex;
    return Function::OK;
}

static void getCoordFromIndex(int _iIndex, int* _piIndexes, int* _piDims, int _iDims)
{
    int iMul = 1;
    for (int i = 0 ; i < _iDims ; i++)
    {
        _piIndexes[i] = (int)(_iIndex / iMul) % _piDims[i];
        iMul *= _piDims[i];
    }
}
