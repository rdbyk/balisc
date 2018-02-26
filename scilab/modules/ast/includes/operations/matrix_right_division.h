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

#ifndef __MATRIX_RDIV__
#define __MATRIX_RDIV__

int	iRightDivisionOfRealMatrix(
    double *_pdblReal1,		int _iRows1,	int _iCols1,
    double *_pdblReal2,		int _iRows2,	int _iCols2,
    double *_pdblRealOut,	int _iRowsOut,	int _iColsOut, double* _pdblRcond);

int	iRightDivisionOfComplexMatrix(
    double *_pdblReal1,		double *_pdblImg1,		int _iRows1,	int _iCols1,
    double *_pdblReal2,		double *_pdblImg2,		int _iRows2,	int _iCols2,
    double *_pdblRealOut,	double *_pdblImgOut,	int _iRowsOut,	int _iColsOut, double *_pdblRcond);

int iRightDivisionRealMatrixByReal(double* A, double b, double* X, int n);
int iRightDivisionComplexMatrixByReal(double* A, double* B, double c, double* X, double* Y, int n);
int iRightDivisionRealMatrixByComplex(double* A, double c, double d, double* X, double* Y, int n);
int iRightDivisionComplexMatrixByComplex(double* A, double* B, double c, double d, double* X,   double* Y, int n);

#endif /* __MATRIX_RDIV__ */
