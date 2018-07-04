/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - INRIA - Antoine ELIAS <antoine.elias@scilab.org>
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

#include <string.h> // for memset function
#include <complex.h>
#if defined(__SSE2__)
#include <emmintrin.h>
#endif
#include "elem_common.h"
#include "matrix_multiplication.h"

void iMultiComplexMatrixByComplexMatrix(
    double *_pdblReal1,		double *_pdblImg1,	int _iRows1, int _iCols1,
    double *_pdblReal2,		double *_pdblImg2,	int _iRows2, int _iCols2,
    double *_pdblRealOut,	double *_pdblImgOut)
{
    double dblOne = 1;
    double dblMinusOne = -1;
    double dblZero = 0;

    int iRowsOut = _iRows1;

    //Cr <-  1*Ar*Br + 0*Cr
    F2C(dgemm)("N", "N", &iRowsOut, &_iCols2, &_iCols1, &dblOne		, _pdblReal1	, &_iRows1, _pdblReal2	, &_iRows2, &dblZero	, _pdblRealOut	, &iRowsOut);
    //Cr <- -1*Ai*Bi + 1*Cr
    F2C(dgemm)("N", "N", &iRowsOut, &_iCols2, &_iCols1, &dblMinusOne	, _pdblImg1		, &_iRows1, _pdblImg2	, &_iRows2, &dblOne		, _pdblRealOut	, &iRowsOut);
    //Ci <-  1*Ar*Bi + 0*Ci
    F2C(dgemm)("N", "N", &iRowsOut, &_iCols2, &_iCols1, &dblOne		, _pdblReal1	, &_iRows1, _pdblImg2	, &_iRows2, &dblZero	, _pdblImgOut	, &iRowsOut);
    //Ci <-  1*Ai*Br + 1*Ci
    F2C(dgemm)("N", "N", &iRowsOut, &_iCols2, &_iCols1, &dblOne		, _pdblImg1		, &_iRows1, _pdblReal2	, &_iRows2, &dblOne		, _pdblImgOut	, &iRowsOut);
}

void iMultiRealMatrixByRealMatrix(
    double *_pdblReal1,	int _iRows1, int _iCols1,
    double *_pdblReal2,	int _iRows2, int _iCols2,
    double *_pdblRealOut)
{
    double dblOne = 1;
    double dblZero = 0;

    C2F(dgemm)("n", "n", &_iRows1, &_iCols2, &_iCols1, &dblOne,
               _pdblReal1 , &_iRows1 ,
               _pdblReal2, &_iRows2, &dblZero,
               _pdblRealOut , &_iRows1);
}

void iMultiRealMatrixByComplexMatrix(
    double *_pdblReal1,		int _iRows1, int _iCols1,
    double *_pdblReal2,		double *_pdblImg2, int _iRows2, int _iCols2,
    double *_pdblRealOut,	double *_pdblImgOut)
{
    double dblOne = 1;
    double dblZero = 0;
    iMultiRealMatrixByRealMatrix(_pdblReal1, _iRows1, _iCols1, _pdblReal2, _iRows2,  _iCols2, _pdblRealOut);
    C2F(dgemm)("n", "n", &_iRows1, &_iCols2, &_iCols1, &dblOne,
               _pdblReal1 , &_iRows1 ,
               _pdblImg2, &_iRows2, &dblZero,
               _pdblImgOut , &_iRows1);
}

void iMultiComplexMatrixByRealMatrix(
    double *_pdblReal1,		double *_pdblImg1,	int _iRows1, int _iCols1,
    double *_pdblReal2,							int _iRows2, int _iCols2,
    double *_pdblRealOut,	double *_pdblImgOut)
{
    double dblOne = 1;
    double dblZero = 0;
    iMultiRealMatrixByRealMatrix(_pdblReal1, _iRows1, _iCols1, _pdblReal2, _iRows2,  _iCols2, _pdblRealOut);
    C2F(dgemm)("n", "n", &_iRows1, &_iCols2, &_iCols1, &dblOne,
               _pdblImg1 , &_iRows1 ,
               _pdblReal2, &_iRows2, &dblZero,
               _pdblImgOut , &_iRows1);
}


void iMultiRealScalarByRealMatrix(double a, double* B, double* X, int n)
{
    // X =  a * B
#if !defined(__SSE2__)
    int iOne = 1;
    int iSize2 = n;

    memmove(X, B, sizeof(double) * iSize2);
    C2F(dscal)(&iSize2, &a, X, &iOne);
#else
    int i = 0;
    for ( ; i < n - 1; i += 2)
    {
        __m128d tmp = _mm_mul_pd(_mm_load1_pd(&a), *((__m128d*)&(B[i])));
        X[i] = tmp[0];
        X[i+1] = tmp[1];
    }

    if (n & 0x1)
    {
        X[i] = a * B[i];
    }
#endif
}

void iMultiRealScalarByComplexMatrix(double a, double* C, double* D,
                                     double* X, double* Y, int n)
{
    // X + Y*i = a * (C + D*i)
#if !defined(__SSE2__)
    int iOne = 1;
    int iSize2 = n;
    
    memmove(X, C, sizeof(double) * iSize2);
    memmove(Y, D, sizeof(double) * iSize2);
    C2F(dscal)(&iSize2, &a, X, &iOne);
    C2F(dscal)(&iSize2, &a, Y, &iOne);
#else
    int i = 0;
    for ( ; i < n - 1; i += 2)
    {
        __m128d aa = _mm_load1_pd(&a);
        __m128d re = _mm_mul_pd(aa, *((__m128d*)&(C[i])));
        X[i] = re[0];
        X[i+1] = re[1];
        __m128d im = _mm_mul_pd(aa, *((__m128d*)&(D[i])));
        Y[i] = im[0];
        Y[i+1] = im[1];
    }

    if (n & 0x1)
    {
        X[i] = a * C[i];
        Y[i] = a * D[i];
    }
#endif
}

void iMultiComplexScalarByRealMatrix(double a, double b, double* C,
                                     double* X, double* Y, int n)
{
    // X + Y*i = (a + b*i) * C
#if !defined(__SSE2__)
    int iOne = 1;
    int iSize2 = n;
    
    memmove(X, C, sizeof(double) * iSize2);
    memmove(Y, C, sizeof(double) * iSize2);
    C2F(dscal)(&iSize2, &a, X, &iOne);
    C2F(dscal)(&iSize2, &b,	Y, &iOne);
#else

    int i = 0;
    for ( ; i < n - 1; i += 2)
    {
        __m128d aa = *((__m128d*)&(C[i]));
        __m128d re = _mm_mul_pd(aa, _mm_load1_pd(&a));
        X[i] = re[0];
        X[i+1] = re[1];
        __m128d im = _mm_mul_pd(aa, _mm_load1_pd(&b));
        Y[i] = im[0];
        Y[i+1] = im[1];
    }

    if (n & 0x1)
    {
        X[i] = a * C[i];
        Y[i] = b * C[i];
    }
#endif
}

void iMultiComplexScalarByComplexMatrix(double a, double b, double* C, double* D,
                                        double* X, double* Y, int n)
{
    // X + Y*i = (a + b*i) * (C + D*i)

    int i;
    for (i = 0; i < n; ++i)
    {
        double complex z = (a + b*I) * (C[i] + D[i]*I);
        X[i] = creal(z);
        Y[i] = cimag(z);
    }
}

/* (a1 + a2 * %s + ... ) * (a1 + a2 * %s + ... )*/
void iMultiScilabPolynomByScilabPolynom(
    double *_pdblReal1,	int _iRank1,
    double *_pdblReal2,	int _iRank2,
    double *_pdblRealOut, int _iRankOut)
{
    int i1 = 0;
    int i2 = 0;
    double dblMult = 0.0;
    double dblAdd = 0.0;

    memset(_pdblRealOut, 0x00, _iRankOut * sizeof(double));

    for (i1 = 0 ; i1 < _iRank1 ; i1++)
    {
        for (i2 = 0 ; i2 < _iRank2 ; i2++)
        {
            _pdblRealOut[i1 + i2] += _pdblReal1[i1] * _pdblReal2[i2];
        }
    }
}

/* ((a1 +ib1) + (a2+ib2) * %s + ... ) (a1 + a2 * %s + ... ) */
void iMultiComplexPolyByScilabPolynom(
    double *_pdblReal1,	double *_pdblImg1, int _iRank1,
    double *_pdblReal2,	int _iRank2,
    double *_pdblRealOut, double *_pdblImgOut, int _iRankOut)
{
    int i1 = 0;
    int i2 = 0;

    memset(_pdblRealOut	, 0x00, _iRankOut * sizeof(double));
    memset(_pdblImgOut	, 0x00, _iRankOut * sizeof(double));

    for (i1 = 0 ; i1 < _iRank1 ; i1++)
    {
        for (i2 = 0 ; i2 < _iRank2 ; i2++)
        {
            _pdblRealOut[i1 + i2] += _pdblReal1[i1] * _pdblReal2[i2];
            _pdblImgOut[i1 + i2]	+= _pdblImg1[i1] * _pdblReal2[i2];
        }
    }
}

/* (a1 + a2 * %s + ... ) * ((a1 +ib1) + (a2+ib2) * %s + ... )*/
void iMultiScilabPolynomByComplexPoly(
    double *_pdblReal1,	int _iRank1,
    double *_pdblReal2,	double *_pdblImg2, int _iRank2,
    double *_pdblRealOut, double *_pdblImgOut, int _iRankOut)
{
    iMultiComplexPolyByScilabPolynom(
               _pdblReal2, _pdblImg2, _iRank2,
               _pdblReal1, _iRank1,
               _pdblRealOut, _pdblImgOut, _iRankOut);
}

/* ((a1 +ib1) + (a2+ib2) * %s + ... ) * ((a1 +ib1) + (a2+ib2) * %s + ... ) */
void iMultiComplexPolyByComplexPoly(
    double *_pdblReal1,	double *_pdblImg1, int _iRank1,
    double *_pdblReal2,	double *_pdblImg2, int _iRank2,
    double *_pdblRealOut, double *_pdblImgOut, int _iRankOut)
{
    int i1 = 0;
    int i2 = 0;

    memset(_pdblRealOut	, 0x00, _iRankOut * sizeof(double));
    memset(_pdblImgOut	, 0x00, _iRankOut * sizeof(double));

    for (i1 = 0 ; i1 < _iRank1 ; i1++)
    {
        for (i2 = 0 ; i2 < _iRank2 ; i2++)
        {
            _pdblRealOut[i1 + i2] += _pdblReal1[i1] * _pdblReal2[i2]	- _pdblImg1[i1] * _pdblImg2[i2];
            _pdblImgOut[i1 + i2]	+= _pdblImg1[i1] * _pdblReal2[i2]		+ _pdblImg2[i2] * _pdblReal1[i1];
        }
    }
}

void iDotMultiplyRealMatrixByRealMatrix(double* A, double* B, double* X, int n)
{
    // X = A .* B

    int i;
    for (i = 0; i < n; ++i)
    {
        X[i] = A[i] * B[i];
    }
}

void iDotMultiplyRealMatrixByComplexMatrix(double* A, double* C, double* D,
                                           double* X, double* Y, int n)
{
    // X + Y*i = A * (C + D*i)

    int i;
    for (i = 0; i < n; ++i)
    {
        X[i] = A[i] * C[i];
        Y[i] = A[i] * D[i];
    }
}

void iDotMultiplyComplexMatrixByComplexMatrix(double* A, double* B, double* C, double* D,
                                              double* X, double* Y, int n)
{
    // X + Y*i = (A + B*i) * (C + D*i)

    int i;
    for (i = 0; i < n; ++i)
    {
        double complex z = (A[i] + B[i]*I) * (C[i] + D[i]*I);
        X[i] = creal(z);
        Y[i] = cimag(z);
    }
}
