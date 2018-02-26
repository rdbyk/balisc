/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Allan CORNET
 * Copyright (C) 2012 - Digiteo - Cedric Delamarre
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
/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "expm.h"
#include "basic_functions.h"
#include "elementary_functions.h"
#include "matrix_left_division.h"
#include "matrix_multiplication.h"
#include "matrix_right_division.h"

int dexpms2(double *_pdblReal, double *_pdblReturnReal, int _iLeadDim)
{
    int iRet = zexpms2(_pdblReal, NULL, _pdblReturnReal, NULL, _iLeadDim);
    return iRet;
}

int zexpms2(double *_pdblReal, double *_pdblImg, double *_pdblReturnReal, double *_pdblReturnImg, int _iLeadDim)
{
    double dblRcond = 0;
    int iRet				= 0;
    int iIndex1			= 0;
    int iMax				= 0;
    int iFlag				= 0;
    int iLoop1			= 0;
    int iSquare			= 0;
    int iOne				= 1;
    int iMallocSize = 0;

    int iComplex = 0;

    double dblZero	= 0;
    double dblOne	= 1;

    int iExp	= 0;
    double dblS		= 0;
    double dblS2	= 0;
    double dblCst	= 0.5;

    double *pdblMatrixRealA		= NULL;//A'
    double *pdblMatrixRealX		= NULL;//X
    double *pdblMatrixRealD		= NULL;//D
    double *pdblMatrixRealcX	= NULL;//cX
    double *pdblMatrixRealcA	= NULL;//cX
    double *pdblMatrixRealEye	= NULL;//Eye
    double *pdblMatrixRealTemp	= NULL;//Temp

    double *pdblMatrixImgA		= NULL;//A'
    double *pdblMatrixImgX		= NULL;//X
    double *pdblMatrixImgD		= NULL;//D
    double *pdblMatrixImgcX		= NULL;//cX
    double *pdblMatrixImgcA		= NULL;//cX
    double *pdblMatrixImgEye	= NULL;//Eye
    double *pdblMatrixImgTemp	= NULL;//Temp

    if (_pdblImg != NULL)
    {
        iComplex = 1;
    }

    iSquare = _iLeadDim * _iLeadDim;
    iMallocSize = sizeof(double) * iSquare;

    pdblMatrixRealA			= (double*)malloc(iMallocSize);
    pdblMatrixRealX			= (double*)malloc(iMallocSize);
    pdblMatrixRealD			= (double*)malloc(iMallocSize);
    pdblMatrixRealcX		= (double*)malloc(iMallocSize);
    pdblMatrixRealcA		= (double*)malloc(iMallocSize);
    pdblMatrixRealEye		= (double*)malloc(iMallocSize);
    pdblMatrixRealTemp		= (double*)malloc(iMallocSize);

    if (iComplex)
    {
        pdblMatrixImgA			= (double*)malloc(iMallocSize);
        pdblMatrixImgX			= (double*)malloc(iMallocSize);
        pdblMatrixImgD			= (double*)malloc(iMallocSize);
        pdblMatrixImgcX			= (double*)malloc(iMallocSize);
        pdblMatrixImgcA			= (double*)malloc(iMallocSize);
        pdblMatrixImgEye		= (double*)malloc(iMallocSize);
        pdblMatrixImgTemp		= (double*)malloc(iMallocSize);

        memset(pdblMatrixImgEye, 0x00, iMallocSize);
    }


    // Scale A by power of 2 so that its norm is < 1/2 .
    frexp(dblGetMatrixInfiniteNorm(_pdblReal, _pdblImg, _iLeadDim, _iLeadDim), &iExp);
    dblS	= Max(0, iExp + 1);
    dblS2	= pow(2, dblS);

    //A = A./2^s
    if (iComplex)
    {
        iRightDivisionComplexMatrixByReal(_pdblReal,_pdblImg, dblS2,
            pdblMatrixRealA, pdblMatrixImgA, iSquare);
    }
    else
    {
        iRightDivisionRealMatrixByReal(_pdblReal, dblS2, pdblMatrixRealA, iSquare);
    }

    // Pade approximation for exp(A)
    //X = A
    memcpy(pdblMatrixRealX, pdblMatrixRealA, iMallocSize);
    if (iComplex)
    {
        memcpy(pdblMatrixImgX, pdblMatrixImgA, iMallocSize);
    }


    // initialize real part of identity matrix
    vDset(iSquare, 0, pdblMatrixRealEye, 1);
    vDset(_iLeadDim, 1, pdblMatrixRealEye, _iLeadDim + 1);

    //cA = A * c
    if (iComplex)
        iMultiRealScalarByComplexMatrix(
            dblCst,
            pdblMatrixRealA, pdblMatrixImgA, _iLeadDim, _iLeadDim,
            pdblMatrixRealcA, pdblMatrixImgcA);
    else
        iMultiRealScalarByRealMatrix(dblCst, pdblMatrixRealA, pdblMatrixRealcA, iSquare);

    //E = Eye + cA
    vDadd(iSquare, pdblMatrixRealEye, pdblMatrixRealcA, 1, 1, _pdblReturnReal);
    if (iComplex)
    {
        vDadd(iSquare, pdblMatrixImgEye, pdblMatrixImgcA, 1, 1, _pdblReturnImg);
    }

    //D = Eye - cA
    vDless(iSquare, pdblMatrixRealEye, pdblMatrixRealcA, 1, 1, pdblMatrixRealD);
    if (iComplex)
    {
        vDless(iSquare, pdblMatrixImgEye, pdblMatrixImgcA, 1, 1, pdblMatrixImgD);
    }

    iMax	= 6;
    iFlag	= 1;

    for (iLoop1 = 2 ; iLoop1 <= iMax ; iLoop1++)
    {
        dblCst	= dblCst * (iMax - iLoop1 + 1 ) / (iLoop1 * (2 * iMax - iLoop1 + 1));

        //Temp = X
        memcpy(pdblMatrixRealTemp, pdblMatrixRealX, iMallocSize);
        if (iComplex)
        {
            memcpy(pdblMatrixImgTemp, pdblMatrixImgX, iMallocSize);
        }

        //X = A * Temp;
        if (iComplex)
        {
            iMultiComplexMatrixByComplexMatrix(
                pdblMatrixRealA, pdblMatrixImgA, _iLeadDim, _iLeadDim,
                pdblMatrixRealTemp, pdblMatrixImgTemp, _iLeadDim, _iLeadDim,
                pdblMatrixRealX, pdblMatrixImgX);
        }
        else
        {
            iMultiRealMatrixByRealMatrix(
                pdblMatrixRealA, _iLeadDim, _iLeadDim,
                pdblMatrixRealTemp, _iLeadDim, _iLeadDim,
                pdblMatrixRealX);
        }
        /*		C2F(dgemm)("n", "n", &_iLeadDim, &_iLeadDim, &_iLeadDim, &dblOne,
        			pdblMatrixRealA, &_iLeadDim ,
        			pdblMatrixRealTemp, &_iLeadDim, &dblZero,
        			pdblMatrixRealX ,&_iLeadDim);
        */
        //cX = c * X
        if (iComplex)
            iMultiRealScalarByComplexMatrix(
                dblCst,
                pdblMatrixRealX, pdblMatrixImgX, _iLeadDim, _iLeadDim,
                pdblMatrixRealcX, pdblMatrixImgcX);
        else
            iMultiRealScalarByRealMatrix(dblCst, pdblMatrixRealX, pdblMatrixRealcX, iSquare);

        //E = E + cX
        vDadd(iSquare, _pdblReturnReal, pdblMatrixRealcX, 1, 1, _pdblReturnReal);
        if (iComplex)
        {
            vDadd(iSquare, _pdblReturnImg, pdblMatrixImgcX, 1, 1, _pdblReturnImg);
        }


        if (iFlag == 1) //D = D + cX
        {
            vDadd(iSquare, pdblMatrixRealD, pdblMatrixRealcX, 1, 1, pdblMatrixRealD);
            if (iComplex)
            {
                vDadd(iSquare, pdblMatrixImgD, pdblMatrixImgcX, 1, 1, pdblMatrixImgD);
            }
        }
        else //D = D - cX
        {
            vDless(iSquare, pdblMatrixRealD, pdblMatrixRealcX, 1, 1, pdblMatrixRealD);
            if (iComplex)
            {
                vDless(iSquare, pdblMatrixImgD, pdblMatrixImgcX, 1, 1, pdblMatrixImgD);
            }
        }

        //Toggle iFlag
        iFlag = !iFlag;
    }

    //Temp = E
    memcpy(pdblMatrixRealTemp, _pdblReturnReal, iMallocSize);
    if (iComplex)
    {
        memcpy(pdblMatrixImgTemp, _pdblReturnImg, iMallocSize);
    }

    //E = D\E
    if (iComplex)
    {
        iRet = iLeftDivisionOfComplexMatrix(
                   pdblMatrixRealD,	pdblMatrixImgD,		_iLeadDim, _iLeadDim,
                   pdblMatrixRealTemp,	pdblMatrixImgTemp,	_iLeadDim, _iLeadDim,
                   _pdblReturnReal,	_pdblReturnImg,		_iLeadDim, _iLeadDim, &dblRcond);
    }
    else
    {
        iRet = iLeftDivisionOfRealMatrix(
                   pdblMatrixRealD,	_iLeadDim, _iLeadDim,
                   pdblMatrixRealTemp,	_iLeadDim, _iLeadDim,
                   _pdblReturnReal,	_iLeadDim, _iLeadDim, &dblRcond);
    }

    if (iRet < 0)
    {
        switch (iRet)
        {
            case -1 :
                //Scilab 6
                //sprintf(C2F(cha1).buf, "%1.4E", dblRcond);
                //Msgs(5,1);
                break;
            case -2 :
                //Scilab 6
                //Msgs(9, (int)dblRcond);
                break;
            default :
                break;
        }
    }
    // Undo scaling by repeated squaring
    for (iLoop1 = 0 ; iLoop1 < dblS ; iLoop1++)
    {
        //Temp = E
        memcpy(pdblMatrixRealTemp, _pdblReturnReal, iMallocSize);
        if (iComplex)
        {
            memcpy(pdblMatrixImgTemp, _pdblReturnImg, iMallocSize);
        }

        // E = E*E
        if (iComplex)
            iMultiComplexMatrixByComplexMatrix(
                pdblMatrixRealTemp, pdblMatrixImgTemp,	_iLeadDim, _iLeadDim,
                pdblMatrixRealTemp, pdblMatrixImgTemp,	_iLeadDim, _iLeadDim,
                _pdblReturnReal,		_pdblReturnImg);
        else
            iMultiRealMatrixByRealMatrix(
                pdblMatrixRealTemp,	_iLeadDim, _iLeadDim,
                pdblMatrixRealTemp,	_iLeadDim, _iLeadDim,
                _pdblReturnReal);
        /*
        		C2F(dgemm)("n", "n", &_iLeadDim, &_iLeadDim, &_iLeadDim, &dblOne,
        			pdblMatrixRealTemp,		&_iLeadDim ,
        			pdblMatrixRealTemp2,	&_iLeadDim, &dblZero,
        			_pdblReturnReal ,		&_iLeadDim);
        */
    }

    free(pdblMatrixRealA);
    free(pdblMatrixRealX);
    free(pdblMatrixRealD);
    free(pdblMatrixRealcX);
    free(pdblMatrixRealcA);
    free(pdblMatrixRealEye);
    free(pdblMatrixRealTemp);

    if (iComplex)
    {
        free(pdblMatrixImgA);
        free(pdblMatrixImgX);
        free(pdblMatrixImgD);
        free(pdblMatrixImgcX);
        free(pdblMatrixImgcA);
        free(pdblMatrixImgEye);
        free(pdblMatrixImgTemp);
    }

    return 0;
}

double dblGetMatrixInfiniteNorm(double *_pdblReal, double *_pdblImg, int _iRows, int _iCols)
{
    int iIndex1 = 0, iIndex2 = 0;
    double dblRef = 0;

    if (_pdblImg == NULL)
    {
        for (iIndex1 = 0 ; iIndex1 < _iRows ; iIndex1++)
        {
            double dblTemp = 0;
            for (iIndex2 = 0 ; iIndex2 < _iCols ; iIndex2++)
            {
                dblTemp += _pdblReal[iIndex1 + iIndex2 * _iRows];
            }
            if (dblTemp > dblRef)
            {
                dblRef = dblTemp;
            }
        }
    }
    else
    {
        for (iIndex1 = 0 ; iIndex1 < _iRows ; iIndex1++)
        {
            double dblTemp = 0;
            for (iIndex2 = 0 ; iIndex2 < _iCols ; iIndex2++)
            {
                dblTemp += hypot(_pdblReal[iIndex1 + iIndex2 * _iRows], _pdblImg[iIndex1 + iIndex2 * _iRows]);
            }
            if (dblTemp > dblRef)
            {
                dblRef = dblTemp;
            }
        }
    }
    return dblRef;
}
