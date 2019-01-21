/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2010-2010 - DIGITEO - Bruno JOFRET
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

#include "types_multiplication.hxx"
#include "types_addition.hxx"
#include "double.hxx"
#include "int.hxx"
#include "sparse.hxx"
#include "polynom.hxx"
#include "singlepoly.hxx"

extern "C"
{
#include "matrix_multiplication.h"
#include "matrix_addition.h"
#include "localization.h"
#include "charEncoding.h"
#include "elem_common.h"
}


using namespace types;

InternalType *GenericTimes(InternalType *_pLeftOperand, InternalType *_pRightOperand)
{
    InternalType *pResult = NULL;
    GenericType::ScilabType TypeL = _pLeftOperand->getType();
    GenericType::ScilabType TypeR = _pRightOperand->getType();

    if (TypeL == GenericType::ScilabDouble && _pLeftOperand->getAs<Double>()->isEmpty() ||
        TypeR == GenericType::ScilabDouble && _pRightOperand->getAs<Double>()->isEmpty())
    {
        return Double::Empty();
    }

    /*
    ** DOUBLE * DOUBLE
    */
    if (TypeL == GenericType::ScilabDouble && TypeR == GenericType::ScilabDouble)
    {
        Double *pL   = _pLeftOperand->getAs<Double>();
        Double *pR   = _pRightOperand->getAs<Double>();

        int iResult = MultiplyDoubleByDouble(pL, pR, (Double**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(3);
        }

        return pResult;
    }

    /*
    ** DOUBLE * POLY
    */
    else if (TypeL == InternalType::ScilabDouble && TypeR == InternalType::ScilabPolynom)
    {
        Double *pL   = _pLeftOperand->getAs<Double>();
        Polynom *pR     = _pRightOperand->getAs<types::Polynom>();

        int iResult = MultiplyDoubleByPoly(pL, pR, (Polynom**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(3);
        }

        return pResult;
    }

    /*
    ** POLY * DOUBLE
    */
    else if (TypeL == InternalType::ScilabPolynom && TypeR == InternalType::ScilabDouble)
    {
        Polynom *pL          = _pLeftOperand->getAs<types::Polynom>();
        Double *pR              = _pRightOperand->getAs<Double>();

        int iResult = MultiplyPolyByDouble(pL, pR, (Polynom**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(3);
        }

        return pResult;
    }

    /*
    ** POLY * POLY
    */
    else if (TypeL == InternalType::ScilabPolynom && TypeR == InternalType::ScilabPolynom)
    {
        Polynom *pL          = _pLeftOperand->getAs<types::Polynom>();
        Polynom *pR          = _pRightOperand->getAs<types::Polynom>();

        if (pL->getVariableName() != pR->getVariableName())
        {
            return NULL; // overload
        }

        int iResult = MultiplyPolyByPoly(pL, pR, (Polynom**)&pResult);

        if (iResult)
        {
            throw ast::InternalError(3);
        }

        return pResult;
    }

    /*
    ** SPARSE * SPARSE
    */
    if (TypeL == GenericType::ScilabSparse && TypeR == GenericType::ScilabSparse)
    {
        Sparse *pL   = _pLeftOperand->getAs<Sparse>();
        Sparse *pR   = _pRightOperand->getAs<Sparse>();

        int iResult = MultiplySparseBySparse(pL, pR, (Sparse**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(3);
        }

        return pResult;
    }

    /*
    ** DOUBLE * SPARSE
    */
    if (TypeL == GenericType::ScilabDouble && TypeR == GenericType::ScilabSparse)
    {
        Double *pL   = _pLeftOperand->getAs<Double>();
        Sparse *pR   = _pRightOperand->getAs<Sparse>();

        int iResult = MultiplyDoubleBySparse(pL, pR, (GenericType**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(3);
        }

        return pResult;
    }

    /*
    ** SPARSE * DOUBLE
    */
    if (TypeL == GenericType::ScilabSparse && TypeR == GenericType::ScilabDouble)
    {
        Sparse *pL   = _pLeftOperand->getAs<Sparse>();
        Double *pR   = _pRightOperand->getAs<Double>();

        int iResult = MultiplySparseByDouble(pL, pR, (GenericType**)&pResult);
        if (iResult)
        {
            throw ast::InternalError(3);
        }

        return pResult;
    }

    /*
    ** Default case : Return NULL will Call Overloading.
    */
    return NULL;

}

int MultiplyDoubleByDouble(Double* _pDouble1, Double* _pDouble2, Double** _pDoubleOut)
{
    if (_pDouble1->isScalar())
    {
        bool bComplex1  = _pDouble1->isComplex();
        bool bComplex2  = _pDouble2->isComplex();

        if (bComplex1 == false && bComplex2 == false)
        {
            (*_pDoubleOut) = _pDouble2->getRef() > 0 ? new Double(_pDouble2->getDims(), _pDouble2->getDimsArray()) : _pDouble2;
            iMultiRealScalarByRealMatrix(_pDouble1->getFirst(), _pDouble2->get(), (*_pDoubleOut)->get(), _pDouble2->getSize());
        }
        else if (bComplex1 == false && bComplex2 == true)
        {
            (*_pDoubleOut) = _pDouble2->getRef() > 0 ? new Double(_pDouble2->getDims(), _pDouble2->getDimsArray(), true) : _pDouble2;
            iMultiRealScalarByComplexMatrix(_pDouble1->getFirst(), _pDouble2->get(), _pDouble2->getImg(), (*_pDoubleOut)->get(), (*_pDoubleOut)->getImg(), _pDouble2->getSize());
        }
        else if (bComplex1 == true && bComplex2 == false)
        {
            (*_pDoubleOut) = new Double(_pDouble2->getDims(), _pDouble2->getDimsArray(), true);
            iMultiComplexScalarByRealMatrix(_pDouble1->getFirst(), _pDouble1->getImgFirst(), _pDouble2->get(), (*_pDoubleOut)->get(), (*_pDoubleOut)->getImg(), _pDouble2->getSize());
        }
        else //if(bComplex1 == true && bComplex2 == true)
        {
            (*_pDoubleOut) = _pDouble2->getRef() > 0 ? new Double(_pDouble2->getDims(), _pDouble2->getDimsArray(), true) : _pDouble2;
            iMultiComplexScalarByComplexMatrix(_pDouble1->getFirst(), _pDouble1->getImgFirst(), _pDouble2->get(), _pDouble2->getImg(), (*_pDoubleOut)->get(), (*_pDoubleOut)->getImg(), _pDouble2->getSize());
        }

        return 0;
    }

    if (_pDouble2->isScalar())
    {
        bool bComplex1  = _pDouble1->isComplex();
        bool bComplex2  = _pDouble2->isComplex();

        if (bComplex1 == false && bComplex2 == false)
        {
            (*_pDoubleOut) = _pDouble1->getRef() > 0 ? new Double(_pDouble1->getDims(), _pDouble1->getDimsArray()) : _pDouble1;
            iMultiRealScalarByRealMatrix(_pDouble2->getFirst(), _pDouble1->get(), (*_pDoubleOut)->get(), _pDouble1->getSize());
        }
        else if (bComplex1 == false && bComplex2 == true)
        {
            (*_pDoubleOut) = new Double(_pDouble1->getDims(), _pDouble1->getDimsArray(), true);
            iMultiComplexScalarByRealMatrix(_pDouble2->getFirst(), _pDouble2->getImgFirst(), _pDouble1->get(), (*_pDoubleOut)->get(), (*_pDoubleOut)->getImg(), _pDouble1->getSize());
        }
        else if (bComplex1 == true && bComplex2 == false)
        {
            (*_pDoubleOut) = _pDouble1->getRef() > 0 ? new Double(_pDouble1->getDims(), _pDouble1->getDimsArray(), true) : _pDouble1;
            iMultiRealScalarByComplexMatrix(_pDouble2->getFirst(), _pDouble1->get(), _pDouble1->getImg(), (*_pDoubleOut)->get(), (*_pDoubleOut)->getImg(), _pDouble1->getSize());
        }
        else //if(bComplex1 == true && bComplex2 == true)
        {
            (*_pDoubleOut) = _pDouble1->getRef() > 0 ? new Double(_pDouble1->getDims(), _pDouble1->getDimsArray(), true) : _pDouble1;
            iMultiComplexScalarByComplexMatrix(_pDouble2->getFirst(), _pDouble2->getImgFirst(), _pDouble1->get(), _pDouble1->getImg(), (*_pDoubleOut)->get(), (*_pDoubleOut)->getImg(), _pDouble1->getSize());
        }

        return 0;
    }

    int r1 = _pDouble1->getRows();
    int c1 = _pDouble1->getCols();
    int r2 = _pDouble2->getRows();
    int c2 = _pDouble2->getCols();

    if (_pDouble1->getDims() == 2 && _pDouble1->getDims() == _pDouble2->getDims() && c1 != r2)
    {
        // Both matrices but with wrong dimensions: error out
        return 1;
    }

    if (_pDouble1->getDims() > 2 || _pDouble2->getDims() > 2 || c1 != r2)
    {
        //call overload
        return 0;
    }

    bool bComplex1  = _pDouble1->isComplex();
    bool bComplex2  = _pDouble2->isComplex();
    (*_pDoubleOut) = new Double(r1, c2, bComplex1 | bComplex2);

    // FIXME: find a better way to detect "eye()*eye()"
    if (r1 == -1)
    {
        // we pretend, that the eye() factors are 1x1-matrices in order
        // to make the following low-level multiplication routines happy
        r1 = 1;
        c1 = 1;
        r2 = 1;
        c2 = 1;
    }

    if (bComplex1 == false && bComplex2 == false)
    {
        //Real Matrix by Real Matrix
        iMultiRealMatrixByRealMatrix(
            _pDouble1->get(), r1, c1,
            _pDouble2->get(), r2, c2,
            (*_pDoubleOut)->get());
    }
    else if (bComplex1 == false && bComplex2 == true)
    {
        //Real Matrix by Matrix Complex
        iMultiRealMatrixByComplexMatrix(
            _pDouble1->get(), r1, c1,
            _pDouble2->get(), _pDouble2->getImg(), r2, c2,
            (*_pDoubleOut)->get(), (*_pDoubleOut)->getImg());
    }
    else if (bComplex1 == true && bComplex2 == false)
    {
        //Complex Matrix by Real Matrix
        iMultiComplexMatrixByRealMatrix(
            _pDouble1->get(), _pDouble1->getImg(), r1, c1,
            _pDouble2->get(), r2, c2,
            (*_pDoubleOut)->get(), (*_pDoubleOut)->getImg());
    }
    else //if(bComplex1 == true && bComplex2 == true)
    {
        //Complex Matrix by Complex Matrix
        iMultiComplexMatrixByComplexMatrix(
            _pDouble1->get(), _pDouble1->getImg(), r1, c1,
            _pDouble2->get(), _pDouble2->getImg(), r2, c2,
            (*_pDoubleOut)->get(), (*_pDoubleOut)->getImg());
    }
    return 0;
}

int MultiplyDoubleByPoly(Double* _pDouble, Polynom* _pPoly, Polynom** _pPolyOut)
{
    bool bComplex1  = _pDouble->isComplex();
    bool bComplex2  = _pPoly->isComplex();

    if (_pDouble->isScalar())
    {
        int* piRank = new int[_pPoly->getSize()];
        for (int i = 0 ; i < _pPoly->getSize() ; i++)
        {
            piRank[i] = _pPoly->get(i)->getRank();
        }

        (*_pPolyOut) = new Polynom(_pPoly->getVariableName(), _pPoly->getDims(), _pPoly->getDimsArray(), piRank);
        delete[] piRank;
        if (bComplex1 || bComplex2)
        {
            (*_pPolyOut)->setComplex(true);
        }

        for (int i = 0 ; i < _pPoly->getSize() ; i++)
        {
            SinglePoly *pPolyIn     = _pPoly->get(i);
            double* pRealIn         = pPolyIn->get();
            double* pImgIn          = pPolyIn->getImg();

            SinglePoly *pPolyOut    = (*_pPolyOut)->get(i);
            double* pRealOut        = pPolyOut->get();
            double* pImgOut         = pPolyOut->getImg();

            if (bComplex1 == false && bComplex2 == false)
            {
                iMultiRealScalarByRealMatrix(_pDouble->getFirst(), pRealIn, pRealOut, pPolyIn->getSize());
            }
            else if (bComplex1 == false && bComplex2 == true)
            {
                iMultiRealScalarByComplexMatrix(_pDouble->getFirst(), pRealIn, pImgIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
            else if (bComplex1 == true && bComplex2 == false)
            {
                iMultiComplexScalarByRealMatrix(_pDouble->getFirst(), _pDouble->getImgFirst(), pRealIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
            else if (bComplex1 == true && bComplex2 == true)
            {
                iMultiComplexScalarByComplexMatrix(_pDouble->getFirst(), _pDouble->getImgFirst(), pRealIn, pImgIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
        }
        (*_pPolyOut)->updateRank();
        return 0;
    }

    if (_pPoly->isScalar())
    {
        int* piRank = new int[_pDouble->getSize()];
        for (int i = 0 ; i < _pDouble->getSize() ; i++)
        {
            piRank[i] = _pPoly->getFirst()->getRank();
        }

        (*_pPolyOut) = new Polynom(_pPoly->getVariableName(), _pDouble->getDims(), _pDouble->getDimsArray(), piRank);
        delete[] piRank;
        if (bComplex1 || bComplex2)
        {
            (*_pPolyOut)->setComplex(true);
        }

        double *pDoubleR    = _pDouble->get();
        double *pDoubleI    = _pDouble->getImg();

        SinglePoly *pPolyIn = _pPoly->getFirst();
        double* pRealIn     = pPolyIn->get();
        double* pImgIn      = pPolyIn->getImg();

        for (int i = 0 ; i < _pDouble->getSize() ; i++)
        {
            SinglePoly *pPolyOut    = (*_pPolyOut)->get(i);
            double* pRealOut        = pPolyOut->get();
            double* pImgOut         = pPolyOut->getImg();

            if (bComplex1 == false && bComplex2 == false)
            {
                iMultiRealScalarByRealMatrix(pDoubleR[i], pRealIn, pRealOut, pPolyIn->getSize());
            }
            else if (bComplex1 == false && bComplex2 == true)
            {
                iMultiRealScalarByComplexMatrix(pDoubleR[i], pRealIn, pImgIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
            else if (bComplex1 == true && bComplex2 == false)
            {
                iMultiComplexScalarByRealMatrix(pDoubleR[i], pDoubleI[i], pRealIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
            else if (bComplex1 == true && bComplex2 == true)
            {
                iMultiComplexScalarByComplexMatrix(pDoubleR[i], pDoubleI[i], pRealIn, pImgIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
        }

        (*_pPolyOut)->updateRank();
        return 0;
    }

    if (_pPoly->getDims() > 2 || _pDouble->getDims() > 2 || _pDouble->getCols() != _pPoly->getRows())
    {
        //call overload
        return 0;
    }

    int* piRank = new int[_pDouble->getRows() * _pPoly->getCols()];
    int iMaxRank = _pPoly->getMaxRank();
    for (int i = 0 ; i < _pDouble->getRows() * _pPoly->getCols() ; i++)
    {
        piRank[i] = iMaxRank;
    }

    (*_pPolyOut) = new Polynom(_pPoly->getVariableName(), _pDouble->getRows(), _pPoly->getCols(), piRank);
    delete[] piRank;
    if (bComplex1 || bComplex2)
    {
        (*_pPolyOut)->setComplex(true);
    }

    Double *pCoef = _pPoly->getCoef();
    Double *pTemp = new Double(_pDouble->getRows(), pCoef->getCols(), bComplex1 || bComplex2);

    if (bComplex1 == false && bComplex2 == false)
    {
        iMultiRealMatrixByRealMatrix(_pDouble->get(), _pDouble->getRows(), _pDouble->getCols(),
                                     pCoef->get(), pCoef->getRows(), pCoef->getCols(),
                                     pTemp->get());
    }
    else if (bComplex1 == false && bComplex2 == true)
    {
        iMultiRealMatrixByComplexMatrix(_pDouble->get(), _pDouble->getRows(), _pDouble->getCols(),
                                        pCoef->get(), pCoef->getImg(), pCoef->getRows(), pCoef->getCols(),
                                        pTemp->get(), pTemp->getImg());

    }
    else if (bComplex1 == true && bComplex2 == false)
    {
        iMultiComplexMatrixByRealMatrix(_pDouble->get(), _pDouble->getImg(), _pDouble->getRows(), _pDouble->getCols(),
                                        pCoef->get(), pCoef->getRows(), pCoef->getCols(),
                                        pTemp->get(), pTemp->getImg());
    }
    else //if(bComplex1 == true && bComplex2 == true)
    {
        iMultiComplexMatrixByComplexMatrix(_pDouble->get(), _pDouble->getImg(), _pDouble->getRows(), _pDouble->getCols(),
                                           pCoef->get(), pCoef->getImg(), pCoef->getRows(), pCoef->getCols(),
                                           pTemp->get(), pTemp->getImg());
    }

    pCoef->killMe();
    (*_pPolyOut)->setCoef(pTemp);
    (*_pPolyOut)->updateRank();
    delete pTemp;
    return 0;
}

int MultiplyPolyByDouble(Polynom* _pPoly, Double* _pDouble, Polynom **_pPolyOut)
{
    bool bComplex1  = _pPoly->isComplex();
    bool bComplex2  = _pDouble->isComplex();
    bool bScalar1   = _pPoly->isScalar();
    bool bScalar2   = _pDouble->isScalar();

    if (bScalar1)
    {
        int* piRank = new int[_pDouble->getSize()];
        for (int i = 0 ; i < _pDouble->getSize() ; i++)
        {
            piRank[i] = _pPoly->getFirst()->getRank();
        }

        (*_pPolyOut) = new Polynom(_pPoly->getVariableName(), _pDouble->getDims(), _pDouble->getDimsArray(), piRank);
        delete[] piRank;
        if (bComplex1 || bComplex2)
        {
            (*_pPolyOut)->setComplex(true);
        }

        double *pDoubleR    = _pDouble->get();
        double *pDoubleI    = _pDouble->getImg();

        SinglePoly *pPolyIn = _pPoly->getFirst();
        double* pRealIn     = pPolyIn->get();
        double* pImgIn      = pPolyIn->getImg();

        for (int i = 0 ; i < _pDouble->getSize() ; i++)
        {
            SinglePoly *pPolyOut    = (*_pPolyOut)->get(i);
            double* pRealOut        = pPolyOut->get();
            double* pImgOut         = pPolyOut->getImg();

            if (bComplex1 == false && bComplex2 == false)
            {
                iMultiRealScalarByRealMatrix(pDoubleR[i], pRealIn, pRealOut, pPolyIn->getSize());
            }
            else if (bComplex1 == false && bComplex2 == true)
            {
                iMultiComplexScalarByRealMatrix(pDoubleR[i], pDoubleI[i], pRealIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
            else if (bComplex1 == true && bComplex2 == false)
            {
                iMultiRealScalarByComplexMatrix(pDoubleR[i], pRealIn, pImgIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
            else if (bComplex1 == true && bComplex2 == true)
            {
                iMultiComplexScalarByComplexMatrix(pDoubleR[i], pDoubleI[i], pRealIn, pImgIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
        }

        (*_pPolyOut)->updateRank();
        return 0;
    }
    else if (bScalar2)
    {
        int* piRank = new int[_pPoly->getSize()];
        for (int i = 0 ; i < _pPoly->getSize() ; i++)
        {
            piRank[i] = _pPoly->get(i)->getRank();
        }

        (*_pPolyOut) = new Polynom(_pPoly->getVariableName(), _pPoly->getDims(), _pPoly->getDimsArray(), piRank);
        delete[] piRank;
        if (bComplex1 || bComplex2)
        {
            (*_pPolyOut)->setComplex(true);
        }

        for (int i = 0 ; i < _pPoly->getSize() ; i++)
        {
            SinglePoly *pPolyIn = _pPoly->get(i);
            double* pRealIn     = pPolyIn->get();
            double* pImgIn      = pPolyIn->getImg();

            SinglePoly *pPolyOut    = (*_pPolyOut)->get(i);
            double* pRealOut        = pPolyOut->get();
            double* pImgOut         = pPolyOut->getImg();

            if (bComplex1 == false && bComplex2 == false)
            {
                iMultiRealScalarByRealMatrix(_pDouble->getFirst(), pRealIn, pRealOut, pPolyIn->getSize());
            }
            else if (bComplex1 == false && bComplex2 == true)
            {
                iMultiComplexScalarByRealMatrix(_pDouble->getFirst(), _pDouble->getImgFirst(), pRealIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
            else if (bComplex1 == true && bComplex2 == false)
            {
                iMultiRealScalarByComplexMatrix(_pDouble->getFirst(), pRealIn, pImgIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
            else if (bComplex1 == true && bComplex2 == true)
            {
                iMultiComplexScalarByComplexMatrix(_pDouble->getFirst(), _pDouble->getImgFirst(), pRealIn, pImgIn, pRealOut, pImgOut, pPolyIn->getSize());
            }
        }

        (*_pPolyOut)->updateRank();
        return 0;
    }

    if (_pDouble->getDims() > 2 || _pPoly->getDims() > 2 || _pPoly->getCols() != _pDouble->getRows())
    {
        //call overload
        return 0;
    }

    int* piRank = new int[_pPoly->getRows() * _pDouble->getCols()];
    int iMaxRank = _pPoly->getMaxRank();
    for (int i = 0 ; i < _pPoly->getRows() * _pDouble->getCols() ; i++)
    {
        piRank[i] = iMaxRank;
    }

    (*_pPolyOut) = new Polynom(_pPoly->getVariableName(), _pPoly->getRows(), _pDouble->getCols(), piRank);
    delete[] piRank;
    if (bComplex1 || bComplex2)
    {
        (*_pPolyOut)->setComplex(true);
    }

    //Distribution a la mano par appels a des sous-fonctions ( iMulti...ScalarBy...Scalar ) plus iAdd...To... )

    //for each line of _pPoly
    for (int iRow1 = 0 ; iRow1 < _pPoly->getRows() ; iRow1++)
    {
        //for each col of _pDouble
        for (int iCol2 = 0 ; iCol2 < _pDouble->getCols() ; iCol2++)
        {
            SinglePoly* pSPOut = (*_pPolyOut)->get(iRow1, iCol2);
            pSPOut->setZeros();

            //for each rows of _pDouble / cols of _pPoly
            for (int iRow2 = 0 ; iRow2 < _pDouble->getRows() ; iRow2++)
            {
                // SinglePoly(iRow1, iRow2) * Double(iRow2, iCol2)
                SinglePoly* pSPIn = _pPoly->get(iRow1, iRow2);
                int iSize = pSPIn->getSize();
                double* pdblMult = new double[iSize];

                if (bComplex1 == false && bComplex2 == false)
                {
                    //Real Matrix by Real Scalar
                    iMultiRealScalarByRealMatrix(_pDouble->get(iRow2, iCol2), pSPIn->get(), pdblMult, iSize);
                    add(pSPOut->get(), (long long)iSize, pdblMult, pSPOut->get());
                }
                else if (bComplex1 == false && bComplex2 == true)
                {
                    //Real Matrix by Scalar Complex
                    double* pdblMultImg = new double[iSize];
                    iMultiComplexScalarByRealMatrix(_pDouble->get(iRow2, iCol2), _pDouble->getImg(iRow2, iCol2), pSPIn->get(), pdblMult, pdblMultImg, pSPIn->getSize());
                    add(pSPOut->get(), pSPOut->getImg(), (long long)iSize, pdblMult, pdblMultImg, pSPOut->get(), pSPOut->getImg());
                    delete[] pdblMultImg;
                }
                else if (bComplex1 == true && bComplex2 == false)
                {
                    double* pdblMultImg = new double[iSize];
                    iMultiRealScalarByComplexMatrix(_pDouble->get(iRow2, iCol2), pSPIn->get(), pSPIn->getImg(), pdblMult, pdblMultImg, pSPIn->getSize());
                    add(pSPOut->get(), pSPOut->getImg(), (long long)iSize, pdblMult, pdblMultImg, pSPOut->get(), pSPOut->getImg());
                    delete[] pdblMultImg;
                }
                else //if(bComplex1 == true && bComplex2 == true)
                {
                    double* pdblMultImg = new double[iSize];
                    iMultiComplexScalarByComplexMatrix(_pDouble->get(iRow2, iCol2), _pDouble->getImg(iRow2, iCol2), pSPIn->get(), pSPIn->getImg(), pdblMult, pdblMultImg, pSPIn->getSize());
                    add(pSPOut->get(), pSPOut->getImg(), (long long)iSize, pdblMult, pdblMultImg, pSPOut->get(), pSPOut->getImg());
                    delete[] pdblMultImg;
                }

                delete[] pdblMult;
            }//for(int iRow2 = 0 ; iRow2 < _pDouble->getRows() ; iRow2++)
        }//for(int iCol2 = 0 ; iCol2 < _pDouble->getCols() ; iCol2++)
    }//for(int iRow1 = 0 ; iRow1 < _pPoly->getRows() ; iRow1++)

    (*_pPolyOut)->updateRank();
    return 0;
}

int MultiplyPolyByPoly(Polynom* _pPoly1, Polynom* _pPoly2, Polynom** _pPolyOut)
{
    bool bComplex1  = _pPoly1->isComplex();
    bool bComplex2  = _pPoly2->isComplex();

    if (_pPoly1->isScalar() && _pPoly2->isScalar())
    {
        //poly1(0) * poly2(0)
        int iRank = _pPoly1->getFirst()->getRank() + _pPoly2->getFirst()->getRank();
        (*_pPolyOut) = new Polynom(_pPoly1->getVariableName(), 1, 1, &iRank);
        if (bComplex1 || bComplex2)
        {
            (*_pPolyOut)->setComplex(true);
        }

        if (bComplex1 == false && bComplex2 == false)
        {
            SinglePoly *pPoly1  = _pPoly1->getFirst();
            SinglePoly *pPoly2  = _pPoly2->getFirst();
            SinglePoly *pPolyOut = (*_pPolyOut)->getFirst();

            pPolyOut->setZeros();

            iMultiScilabPolynomByScilabPolynom(
                pPoly1->get(), pPoly1->getSize(),
                pPoly2->get(), pPoly2->getSize(),
                pPolyOut->get(), pPolyOut->getSize());
        }
        else if (bComplex1 == false && bComplex2 == true)
        {
            SinglePoly *pPoly1  = _pPoly1->getFirst();
            SinglePoly *pPoly2  = _pPoly2->getFirst();
            SinglePoly *pPolyOut = (*_pPolyOut)->getFirst();

            pPolyOut->setZeros();

            iMultiScilabPolynomByComplexPoly(
                pPoly1->get(), pPoly1->getSize(),
                pPoly2->get(), pPoly2->getImg(), pPoly2->getSize(),
                pPolyOut->get(), pPolyOut->getImg(), pPolyOut->getSize());
        }
        else if (bComplex1 == true && bComplex2 == false)
        {
            SinglePoly *pPoly1  = _pPoly1->getFirst();
            SinglePoly *pPoly2  = _pPoly2->getFirst();
            SinglePoly *pPolyOut = (*_pPolyOut)->getFirst();

            pPolyOut->setZeros();

            iMultiComplexPolyByScilabPolynom(
                pPoly1->get(), pPoly1->getImg(), pPoly1->getSize(),
                pPoly2->get(), pPoly2->getSize(),
                pPolyOut->get(), pPolyOut->getImg(), pPolyOut->getSize());
        }
        else if (bComplex1 == true && bComplex2 == true)
        {
            SinglePoly *pPoly1   = _pPoly1->getFirst();
            SinglePoly *pPoly2   = _pPoly2->getFirst();
            SinglePoly *pPolyOut  = (*_pPolyOut)->getFirst();

            pPolyOut->setZeros();

            iMultiComplexPolyByComplexPoly(
                pPoly1->get(), pPoly1->getImg(), pPoly1->getSize(),
                pPoly2->get(), pPoly2->getImg(), pPoly2->getSize(),
                pPolyOut->get(), pPolyOut->getImg(), pPolyOut->getSize());
        }

        (*_pPolyOut)->updateRank();
        return 0;
    }

    if (_pPoly1->isScalar())
    {
        //poly1(0) * poly2(n)
        int* piRank = new int[_pPoly2->getSize()];
        for (int i = 0 ; i < _pPoly2->getSize() ; i++)
        {
            piRank[i] = _pPoly1->getFirst()->getRank() + _pPoly2->get(i)->getRank();
        }

        (*_pPolyOut) = new Polynom(_pPoly1->getVariableName(), _pPoly2->getDims(), _pPoly2->getDimsArray(), piRank);
        if (bComplex1 || bComplex2)
        {
            (*_pPolyOut)->setComplex(true);
        }
        delete[] piRank;


        SinglePoly *pPoly1  = _pPoly1->getFirst();
        if (bComplex1 == false && bComplex2 == false)
        {
            for (int iPoly = 0 ; iPoly < _pPoly2->getSize() ; iPoly++)
            {
                SinglePoly *pPoly2  = _pPoly2->get(iPoly);
                SinglePoly *pPolyOut = (*_pPolyOut)->get(iPoly);

                pPolyOut->setZeros();

                iMultiScilabPolynomByScilabPolynom(
                    pPoly1->get(), pPoly1->getSize(),
                    pPoly2->get(), pPoly2->getSize(),
                    pPolyOut->get(), pPolyOut->getSize());
            }
        }
        else if (bComplex1 == false && bComplex2 == true)
        {
            for (int iPoly = 0 ; iPoly < _pPoly2->getSize() ; iPoly++)
            {
                SinglePoly *pPoly2  = _pPoly2->get(iPoly);
                SinglePoly *pPolyOut = (*_pPolyOut)->get(iPoly);

                pPolyOut->setZeros();

                iMultiScilabPolynomByComplexPoly(
                    pPoly1->get(), pPoly1->getSize(),
                    pPoly2->get(), pPoly2->getImg(), pPoly2->getSize(),
                    pPolyOut->get(), pPolyOut->getImg(), pPolyOut->getSize());
            }
        }
        else if (bComplex1 == true && bComplex2 == false)
        {
            for (int iPoly = 0 ; iPoly < _pPoly2->getSize() ; iPoly++)
            {
                SinglePoly *pPoly2  = _pPoly2->get(iPoly);
                SinglePoly *pPolyOut = (*_pPolyOut)->get(iPoly);

                pPolyOut->setZeros();

                iMultiComplexPolyByScilabPolynom(
                    pPoly1->get(), pPoly1->getImg(), pPoly1->getSize(),
                    pPoly2->get(), pPoly2->getSize(),
                    pPolyOut->get(), pPolyOut->getImg(), pPolyOut->getSize());
            }
        }
        else if (bComplex1 == true && bComplex2 == true)
        {
            for (int iPoly = 0 ; iPoly < _pPoly2->getSize() ; iPoly++)
            {
                SinglePoly *pPoly2   = _pPoly2->get(iPoly);
                SinglePoly *pPolyOut  = (*_pPolyOut)->get(iPoly);

                pPolyOut->setZeros();

                iMultiComplexPolyByComplexPoly(
                    pPoly1->get(), pPoly1->getImg(), pPoly1->getSize(),
                    pPoly2->get(), pPoly2->getImg(), pPoly2->getSize(),
                    pPolyOut->get(), pPolyOut->getImg(), pPolyOut->getSize());
            }
        }

        (*_pPolyOut)->updateRank();
        return 0;
    }

    if (_pPoly2->isScalar())
    {
        //poly1(n) * poly2(0)
        int* piRank = new int[_pPoly1->getSize()];
        for (int i = 0 ; i < _pPoly1->getSize() ; i++)
        {
            piRank[i] = _pPoly2->getFirst()->getRank() + _pPoly1->get(i)->getRank();
        }

        (*_pPolyOut) = new Polynom(_pPoly1->getVariableName(), _pPoly1->getDims(), _pPoly1->getDimsArray(), piRank);
        if (bComplex1 || bComplex2)
        {
            (*_pPolyOut)->setComplex(true);
        }
        delete[] piRank;

        SinglePoly *pPoly2  = _pPoly2->getFirst();
        if (bComplex1 == false && bComplex2 == false)
        {
            for (int iPoly = 0 ; iPoly < _pPoly1->getSize() ; iPoly++)
            {
                SinglePoly *pPoly1  = _pPoly1->get(iPoly);
                SinglePoly *pPolyOut = (*_pPolyOut)->get(iPoly);

                pPolyOut->setZeros();

                iMultiScilabPolynomByScilabPolynom(
                    pPoly1->get(), pPoly1->getSize(),
                    pPoly2->get(), pPoly2->getSize(),
                    pPolyOut->get(), pPolyOut->getSize());
            }
        }
        else if (bComplex1 == false && bComplex2 == true)
        {
            for (int iPoly = 0 ; iPoly < _pPoly1->getSize() ; iPoly++)
            {
                SinglePoly *pPoly1  = _pPoly1->get(iPoly);
                SinglePoly *pPolyOut = (*_pPolyOut)->get(iPoly);

                pPolyOut->setZeros();

                iMultiScilabPolynomByComplexPoly(
                    pPoly1->get(), pPoly1->getSize(),
                    pPoly2->get(), pPoly2->getImg(), pPoly2->getSize(),
                    pPolyOut->get(), pPolyOut->getImg(), pPolyOut->getSize());
            }
        }
        else if (bComplex1 == true && bComplex2 == false)
        {
            for (int iPoly = 0 ; iPoly < _pPoly1->getSize() ; iPoly++)
            {
                SinglePoly *pPoly1  = _pPoly1->get(iPoly);
                SinglePoly *pPolyOut = (*_pPolyOut)->get(iPoly);

                pPolyOut->setZeros();

                iMultiComplexPolyByScilabPolynom(
                    pPoly1->get(), pPoly1->getImg(), pPoly1->getSize(),
                    pPoly2->get(), pPoly2->getSize(),
                    pPolyOut->get(), pPolyOut->getImg(), pPolyOut->getSize());
            }
        }
        else if (bComplex1 == true && bComplex2 == true)
        {
            for (int iPoly = 0 ; iPoly < _pPoly1->getSize() ; iPoly++)
            {
                SinglePoly *pPoly1   = _pPoly1->get(iPoly);
                SinglePoly *pPolyOut  = (*_pPolyOut)->get(iPoly);

                pPolyOut->setZeros();

                iMultiComplexPolyByComplexPoly(
                    pPoly1->get(), pPoly1->getImg(), pPoly1->getSize(),
                    pPoly2->get(), pPoly2->getImg(), pPoly2->getSize(),
                    pPolyOut->get(), pPolyOut->getImg(), pPolyOut->getSize());
            }
        }

        (*_pPolyOut)->updateRank();
        return 0;
    }

    if (_pPoly1->getDims() > 2 || _pPoly2->getDims() > 2 || _pPoly1->getCols() != _pPoly2->getRows())
    {
        //call overload
        return 0;
    }

    // matrix by matrix
    int* piRank = new int[_pPoly1->getRows() * _pPoly2->getCols()];
    int iMaxRank = _pPoly1->getMaxRank() + _pPoly2->getMaxRank();
    for (int i = 0 ; i < _pPoly1->getRows() * _pPoly2->getCols() ; i++)
    {
        piRank[i] = iMaxRank;
    }

    (*_pPolyOut) = new Polynom(_pPoly1->getVariableName(), _pPoly1->getRows(), _pPoly2->getCols(), piRank);
    if (bComplex1 || bComplex2)
    {
        (*_pPolyOut)->setComplex(true);
    }

    delete[] piRank;


    if (bComplex1 == false && bComplex2 == false)
    {
        double *pReal = NULL;
        SinglePoly *pTemp  = new SinglePoly(&pReal, (*_pPolyOut)->getMaxRank());

        for (int iRow = 0 ; iRow < _pPoly1->getRows() ; iRow++)
        {
            for (int iCol = 0 ; iCol < _pPoly2->getCols() ; iCol++)
            {
                SinglePoly *pResult = (*_pPolyOut)->get(iRow, iCol);
                pResult->setZeros();

                for (int iCommon = 0 ; iCommon < _pPoly1->getCols() ; iCommon++)
                {
                    SinglePoly *pL   = _pPoly1->get(iRow, iCommon);
                    SinglePoly *pR   = _pPoly2->get(iCommon, iCol);

                    pTemp->setZeros();

                    iMultiScilabPolynomByScilabPolynom(
                        pL->get(), pL->getSize(),
                        pR->get(), pR->getSize(),
                        pTemp->get(), pL->getRank() + pR->getRank() + 1);

                    iAddScilabPolynomToScilabPolynom(
                        pResult->get(), pResult->getSize(),
                        pTemp->get(), pResult->getSize(),
                        pResult->get(), pResult->getSize());
                }
            }
        }

        pTemp->killMe();
    }
    else if (bComplex1 == false && bComplex2 == true)
    {
        double *pReal = NULL;
        double *pImg = NULL;
        SinglePoly *pTemp  = new SinglePoly(&pReal, &pImg, (*_pPolyOut)->getMaxRank());

        for (int iRow = 0 ; iRow < _pPoly1->getRows() ; iRow++)
        {
            for (int iCol = 0 ; iCol < _pPoly2->getCols() ; iCol++)
            {
                SinglePoly *pResult = (*_pPolyOut)->get(iRow, iCol);
                pResult->setZeros();

                for (int iCommon = 0 ; iCommon < _pPoly1->getCols() ; iCommon++)
                {
                    SinglePoly *pL   = _pPoly1->get(iRow, iCommon);
                    SinglePoly *pR   = _pPoly2->get(iCommon, iCol);

                    pTemp->setZeros();

                    iMultiScilabPolynomByComplexPoly(
                        pL->get(), pL->getSize(),
                        pR->get(), pR->getImg(), pR->getSize(),
                        pTemp->get(), pTemp->getImg(), pL->getRank() + pR->getRank() + 1);

                    iAddComplexPolyToComplexPoly(
                        pResult->get(), pResult->getImg(), pResult->getSize(),
                        pTemp->get(), pTemp->getImg(), pResult->getSize(),
                        pResult->get(), pResult->getImg(), pResult->getSize());
                }
            }
        }

        pTemp->killMe();
    }
    else if (bComplex1 == true && bComplex2 == false)
    {
        double *pReal = NULL;
        double *pImg = NULL;
        SinglePoly *pTemp  = new SinglePoly(&pReal, &pImg, (*_pPolyOut)->getMaxRank());

        for (int iRow = 0 ; iRow < _pPoly1->getRows() ; iRow++)
        {
            for (int iCol = 0 ; iCol < _pPoly2->getCols() ; iCol++)
            {
                SinglePoly *pResult = (*_pPolyOut)->get(iRow, iCol);
                pResult->setZeros();

                for (int iCommon = 0 ; iCommon < _pPoly1->getCols() ; iCommon++)
                {
                    SinglePoly *pL   = _pPoly1->get(iRow, iCommon);
                    SinglePoly *pR   = _pPoly2->get(iCommon, iCol);

                    pTemp->setZeros();

                    iMultiScilabPolynomByComplexPoly(
                        pR->get(), pR->getSize(),
                        pL->get(), pL->getImg(), pL->getSize(),
                        pTemp->get(), pTemp->getImg(), pL->getRank() + pR->getRank() + 1);

                    iAddComplexPolyToComplexPoly(
                        pResult->get(), pResult->getImg(), pResult->getSize(),
                        pTemp->get(), pTemp->getImg(), pResult->getSize(),
                        pResult->get(), pResult->getImg(), pResult->getSize());
                }
            }
        }

        pTemp->killMe();
    }
    else if (bComplex1 == true && bComplex2 == true)
    {
        double *pReal = NULL;
        double *pImg = NULL;
        SinglePoly *pTemp  = new SinglePoly(&pReal, &pImg, (*_pPolyOut)->getMaxRank());

        for (int iRow = 0 ; iRow < _pPoly1->getRows() ; iRow++)
        {
            for (int iCol = 0 ; iCol < _pPoly2->getCols() ; iCol++)
            {
                SinglePoly *pResult = (*_pPolyOut)->get(iRow, iCol);
                pResult->setZeros();

                for (int iCommon = 0 ; iCommon < _pPoly1->getCols() ; iCommon++)
                {
                    SinglePoly *pL   = _pPoly1->get(iRow, iCommon);
                    SinglePoly *pR   = _pPoly2->get(iCommon, iCol);

                    pTemp->setZeros();

                    iMultiComplexPolyByComplexPoly(
                        pL->get(), pL->getImg(), pL->getSize(),
                        pR->get(), pR->getImg(), pR->getSize(),
                        pTemp->get(), pTemp->getImg(), pL->getRank() + pR->getRank() + 1);

                    iAddComplexPolyToComplexPoly(
                        pResult->get(), pResult->getImg(), pResult->getSize(),
                        pTemp->get(), pTemp->getImg(), pResult->getSize(),
                        pResult->get(), pResult->getImg(), pResult->getSize());
                }
            }
        }

        pTemp->killMe();
    }
    (*_pPolyOut)->updateRank();

    return 0;
}

int MultiplySparseBySparse(Sparse* _pSparse1, Sparse* _pSparse2, Sparse** _pSparseOut)
{
    if (_pSparse1->isScalar())
    {
        //scalar * sp
        Double* pDbl = NULL;
        if (_pSparse1->isComplex())
        {
            std::complex<double> dbl = _pSparse1->getFirst();
            pDbl = new Double(dbl.real(), dbl.imag());
        }
        else
        {
            pDbl = new Double(_pSparse1->getFirst());
        }

        MultiplyDoubleBySparse(pDbl, _pSparse2, (GenericType**)_pSparseOut);
        delete pDbl;
        return 0;
    }

    if (_pSparse2->isScalar())
    {
        //sp * scalar
        Double* pDbl = NULL;
        if (_pSparse2->isComplex())
        {
            std::complex<double> dbl = _pSparse2->getFirst();
            pDbl = new Double(dbl.real(), dbl.imag());
        }
        else
        {
            pDbl = new Double(_pSparse2->getFirst());
        }

        MultiplySparseByDouble(_pSparse1, pDbl, (GenericType**)_pSparseOut);
        delete pDbl;
        return 0;
    }

    if (_pSparse1->getCols() != _pSparse2->getRows())
    {
        return 1;
    }

    *_pSparseOut = _pSparse1->multiply(*_pSparse2);
    return 0;
}

int MultiplyDoubleBySparse(Double* _pDouble, Sparse *_pSparse, GenericType** _pOut)
{
    //D * SP
    if (_pDouble->isScalar())
    {
        //d * SP -> SP
        Sparse* pOut = NULL;
        if (_pDouble->isComplex())
        {
            std::complex<double> dbl(_pDouble->getFirst(), _pDouble->getImgFirst());
            pOut = _pSparse->multiply(dbl);
        }
        else
        {
            pOut = _pSparse->multiply(_pDouble->getFirst());
        }
        *_pOut = pOut;
        return 0;
    }

    if (_pSparse->isScalar())
    {
        //D * sp -> D .* d
        Double* pD = NULL;

        if (_pSparse->isComplex())
        {
            std::complex<double> dbl(_pSparse->getFirst());
            pD = new Double(dbl.real(), dbl.imag());
        }
        else
        {
            pD = new Double(_pSparse->getFirst());
        }

        InternalType* pIT = GenericDotTimes(_pDouble, pD);
        *_pOut = pIT->getAs<GenericType>();
        delete pD;
        return 0;
    }

    if (_pDouble->getDims() > 2)
    {
        //call overload
        return 0;
    }

    if (_pDouble->getCols() != _pSparse->getRows())
    {
        return 1;
    }

    //try to be smart and only compute for non zero values

    //get some information
    int iNonZeros = static_cast<int>(_pSparse->nonZeros());
    int* pRows = new int[iNonZeros * 2];
    _pSparse->outputRowCol(pRows);
    int* pCols = pRows + iNonZeros;
    double* pValR = new double[iNonZeros];
    double* pValI = new double[iNonZeros];
    _pSparse->outputValues(pValR, pValI);

    Double* pOut = new Double(_pDouble->getRows(), _pSparse->getCols(), _pDouble->isComplex() | _pSparse->isComplex());
    pOut->setZeros();

    if (_pDouble->isComplex() == false && _pSparse->isComplex() == false)
    {
        for (int i = 0 ; i < iNonZeros ; i++)
        {
            int iRow = static_cast<int>(pRows[i]) - 1;
            int iCol = static_cast<int>(pCols[i]) - 1;
            double dbl = pValR[i];

            for (int j = 0 ; j < _pDouble->getRows() ; j++)
            {
                double dblVal = _pDouble->get(j, iRow) * dbl;
                pOut->set(j, iCol, pOut->get(j, iCol) + dblVal);
            }
        }
    }
    else if (_pDouble->isComplex() == false && _pSparse->isComplex() == true)
    {
        //a * (b ci) -> ab ac
        for (int i = 0 ; i < iNonZeros ; i++)
        {
            int iRow = static_cast<int>(pRows[i]) - 1;
            int iCol = static_cast<int>(pCols[i]) - 1;
            double dblR = pValR[i];
            double dblI = pValI[i];

            for (int j = 0 ; j < _pDouble->getRows() ; j++)
            {
                double dblValR = _pDouble->get(j, iRow) * dblR;
                double dblValI = _pDouble->get(j, iRow) * dblI;
                pOut->set(j, iCol, pOut->get(j, iCol) + dblValR);
                pOut->setImg(j, iCol, pOut->getImg(j, iCol) + dblValI);
            }
        }
    }
    else if (_pDouble->isComplex() == true && _pSparse->isComplex() == false)
    {
        //(a bi) * c -> ac + bc
        for (int i = 0 ; i < iNonZeros ; i++)
        {
            int iRow = static_cast<int>(pRows[i]) - 1;
            int iCol = static_cast<int>(pCols[i]) - 1;
            double dblR = pValR[i];

            for (int j = 0 ; j < _pDouble->getRows() ; j++)
            {
                double dblValR = _pDouble->get(j, iRow) * dblR;
                double dblValI = _pDouble->getImg(j, iRow) * dblR;
                pOut->set(j, iCol, pOut->get(j, iCol) + dblValR);
                pOut->setImg(j, iCol, pOut->getImg(j, iCol) + dblValI);
            }
        }
    }
    else if (_pDouble->isComplex() == true && _pSparse->isComplex() == true)
    {
        for (int i = 0 ; i < iNonZeros ; i++)
        {
            int iRow = static_cast<int>(pRows[i]) - 1;
            int iCol = static_cast<int>(pCols[i]) - 1;
            double dblR = pValR[i];
            double dblI = pValI[i];

            for (int j = 0 ; j < _pDouble->getRows() ; j++)
            {
                double dblValR = _pDouble->get(j, iRow) * dblR - _pDouble->getImg(j, iRow) * dblI;
                double dblValI = _pDouble->get(j, iRow) * dblI + _pDouble->getImg(j, iRow) * dblR;
                pOut->set(j, iCol, pOut->get(j, iCol) + dblValR);
                pOut->setImg(j, iCol, pOut->getImg(j, iCol) + dblValI);
            }
        }
    }

    *_pOut = pOut;
    delete[] pRows;
    delete[] pValR;
    delete[] pValI;

    return 0;
}

int MultiplySparseByDouble(Sparse *_pSparse, Double*_pDouble, GenericType** _pOut)
{
    if (_pDouble->isScalar())
    {
        //SP * d -> SP
        Sparse* pOut = NULL;
        if (_pDouble->isComplex())
        {
            std::complex<double> dbl(_pDouble->getFirst(), _pDouble->getImgFirst());
            pOut = _pSparse->multiply(dbl);
        }
        else
        {
            pOut = _pSparse->multiply(_pDouble->getFirst());
        }
        *_pOut = pOut;
        return 0;
    }

    if (_pSparse->isScalar())
    {
        //D * sp -> D .* d
        Double* pD = NULL;

        if (_pSparse->isComplex())
        {
            std::complex<double> dbl(_pSparse->getFirst());
            pD = new Double(dbl.real(), dbl.imag());
        }
        else
        {
            pD = new Double(_pSparse->getFirst());
        }

        InternalType* pIT = GenericDotTimes(_pDouble, pD);
        *_pOut = pIT->getAs<GenericType>();
        delete pD;
        return 0;
    }

    if (_pDouble->getDims() > 2)
    {
        //call overload
        return 0;
    }

    if (_pSparse->getCols() != _pDouble->getRows())
    {
        return 1;
    }

    //try to be smart and only compute for non zero values

    //get some information
    int iNonZeros = static_cast<int>(_pSparse->nonZeros());
    int* pRows = new int[iNonZeros * 2];
    _pSparse->outputRowCol(pRows);
    int* pCols = pRows + iNonZeros;
    double* pValR = new double[iNonZeros];
    double* pValI = new double[iNonZeros];
    _pSparse->outputValues(pValR, pValI);

    Double* pOut = new Double(_pSparse->getRows(), _pDouble->getCols(), _pDouble->isComplex() | _pSparse->isComplex());
    pOut->setZeros();

    if (_pDouble->isComplex() == false && _pSparse->isComplex() == false)
    {
        for (int i = 0 ; i < iNonZeros ; i++)
        {
            int iRow    = static_cast<int>(pRows[i]) - 1;
            int iCol    = static_cast<int>(pCols[i]) - 1;
            double dbl  = pValR[i];

            for (int j = 0 ; j < _pDouble->getCols() ; j++)
            {
                double dblVal = _pDouble->get(iCol, j) * dbl;
                pOut->set(iRow, j, pOut->get(iRow, j) + dblVal);
            }
        }
    }
    else if (_pDouble->isComplex() == false && _pSparse->isComplex() == true)
    {
        //a * (b ci) -> ab ac
        for (int i = 0 ; i < iNonZeros ; i++)
        {
            int iRow = static_cast<int>(pRows[i]) - 1;
            int iCol = static_cast<int>(pCols[i]) - 1;
            double dblR = pValR[i];
            double dblI = pValI[i];

            for (int j = 0 ; j < _pDouble->getCols() ; j++)
            {
                double dblValR = _pDouble->get(iCol, j) * dblR;
                double dblValI = _pDouble->get(iCol, j) * dblI;
                pOut->set(iRow, j, pOut->get(iRow, j) + dblValR);
                pOut->setImg(iRow, j, pOut->getImg(iRow, j) + dblValI);
            }
        }
    }
    else if (_pDouble->isComplex() == true && _pSparse->isComplex() == false)
    {
        //(a bi) * c -> ac + bc
        for (int i = 0 ; i < iNonZeros ; i++)
        {
            int iRow = static_cast<int>(pRows[i]) - 1;
            int iCol = static_cast<int>(pCols[i]) - 1;
            double dblR = pValR[i];

            for (int j = 0 ; j < _pDouble->getCols() ; j++)
            {
                double dblValR = _pDouble->get(iCol, j) * dblR;
                double dblValI = _pDouble->getImg(iCol, j) * dblR;
                pOut->set(iRow, j, pOut->get(iRow, j) + dblValR);
                pOut->setImg(iRow, j, pOut->getImg(iRow, j) + dblValI);
            }
        }
    }
    else if (_pDouble->isComplex() == true && _pSparse->isComplex() == true)
    {
        for (int i = 0 ; i < iNonZeros ; i++)
        {
            int iRow = static_cast<int>(pRows[i]) - 1;
            int iCol = static_cast<int>(pCols[i]) - 1;
            double dblR = pValR[i];
            double dblI = pValI[i];

            for (int j = 0 ; j < _pDouble->getCols() ; j++)
            {
                double dblValR = _pDouble->get(iCol, j) * dblR - _pDouble->getImg(iCol, j) * dblI;
                double dblValI = _pDouble->get(iCol, j) * dblI + _pDouble->getImg(iCol, j) * dblR;
                pOut->set(iRow, j, pOut->get(iRow, j) + dblValR);
                pOut->setImg(iRow, j, pOut->getImg(iRow, j) + dblValI);
            }
        }
    }

    *_pOut = pOut;
    delete[] pRows;
    delete[] pValR;
    delete[] pValI;

    return 0;
}
