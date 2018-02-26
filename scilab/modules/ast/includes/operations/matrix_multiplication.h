/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
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

#ifndef __MATRIX_MULT__
#define __MATRIX_MULT__

void iMultiComplexMatrixByComplexMatrix(
    double *_pdblReal1,		double *_pdblImg1, int _iRows1, int _iCols1,
    double *_pdblReal2,		double *_pdblImg2, int _iRows2, int _iCols2,
    double *_pdblRealOut,	double *_pdblImgOut);

void iMultiRealMatrixByRealMatrix(
    double *_pdblReal1,	int _iRows1, int _iCols1,
    double *_pdblReal2,	int _iRows2, int _iCols2,
    double *_pdblRealOut);

void iMultiRealMatrixByComplexMatrix(
    double *_pdblReal1,		int _iRows1, int _iCols1,
    double *_pdblReal2,		double *_pdblImg2, int _iRows2, int _iCols2,
    double *_pdblRealOut,	double *_pdblImgOut);

void iMultiComplexMatrixByRealMatrix(
    double *_pdblReal1,		double *_pdblImg1,	int _iRows1, int _iCols1,
    double *_pdblReal2,		int _iRows2, int _iCols2,
    double *_pdblRealOut,	double *_pdblImgOut);

void iMultiRealScalarByRealMatrix(double a, double* B, double* X, int n);

void iMultiRealScalarByComplexMatrix(
    double _dblReal1,
    double *_pdblReal2,	double *_pdblImg2, int _iRows2, int _iCols2,
    double *_pdblRealOut, double *_pdblImgOut);

void iMultiComplexScalarByRealMatrix(
    double _dblReal1,		double _dblImg1,
    double *_pdblReal2,		int _iRows2, int _iCols2,
    double *_pdblRealOut,	double *_pdblImgOut);

void iMultiComplexScalarByComplexMatrix(double a, double b, double* C, double* D, double* X, double* Y, int n);

/*polynomial multiplications*/
void iMultiScilabPolynomByScilabPolynom(
    double *_pdblReal1,	int _iRank1,
    double *_pdblReal2,	int _iRank2,
    double *_pdblRealOut, int _iRankOut);

void iMultiComplexPolyByScilabPolynom(
    double *_pdblReal1,	double *_pdblImg1, int _iRank1,
    double *_pdblReal2,	int _iRank2,
    double *_pdblRealOut, double *_pdblImgOut, int _iRankOut);

void iMultiScilabPolynomByComplexPoly(
    double *_pdblReal1,	int _iRank1,
    double *_pdblReal2,	double *_pdblImg2, int _iRank2,
    double *_pdblRealOut, double *_pdblImgOut, int _iRankOut);

void iMultiComplexPolyByComplexPoly(
    double *_pdblReal1,	double *_pdblImg1, int _iRank1,
    double *_pdblReal2,	double *_pdblImg2, int _iRank2,
    double *_pdblRealOut, double *_pdblImgOut, int _iRankOut);

void iDotMultiplyRealMatrixByRealMatrix(double* A, double* B, double* X, int n);
void iDotMultiplyRealMatrixByComplexMatrix(double* A, double* C, double* D, double* X, double* Y, int n);

void iDotMultiplyComplexMatrixByComplexMatrix(
    double* _pdblReal1, double* _pdblImg1,
    double* _pdblReal2, double* _pdblImg2,
    double* _pdblRealOut, double* _pdblImgOut, int _iRowsOut, int _iColsOut);

#endif /* __MATRIX_MULT__ */
