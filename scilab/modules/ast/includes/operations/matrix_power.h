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

#ifndef __MATRIC_POWER_H__
#define __MATRIC_POWER_H__

//Scalar ^ Scalar
void iPowerRealScalarByRealScalar(
    double _dblReal1,
    double _dblReal2,
    double* _pdblRealOut, double* _pdblImgOut, int *_piComplex);

void iPowerRealScalarByComplexScalar(
    double _dblReal1,
    double _dblReal2, double _dblImg2,
    double* _pdblRealOut, double* _pdblImgOut);

void iPowerComplexScalarByRealScalar(
    double _dblReal1, double _dblImg1,
    double _dblReal2,
    double* _pdblRealOut, double* _pdblImgOut);

void iPowerComplexScalarByComplexScalar(
    double _dblReal1, double _dblImg1,
    double _dblReal2, double _dblImg2, double* _pdblRealOut, double* _pdblImgOut);

//Scalar ^ Matrix
void iPowerRealScalarByRealMatrix(
    double _dblReal1,
    double* _pdblReal2, int _iSize2,
    double* _pdblRealOut,	double* _pdblImgOut, int *_iComplex);

void iPowerComplexScalarByRealMatrix(
    double _dblReal1, double _dblImg1,
    double* _pdblReal2, int _iSize2,
    double* _pdblRealOut,	double* _pdblImgOut);

void iPowerRealScalarByComplexMatrix(
    double _dblReal1,
    double* _pdblReal2, double* _pdblImg2, int _iSize2,
    double* _pdblRealOut,	double* _pdblImgOut);

void iPowerComplexScalarByComplexMatrix(
    double _dblReal1, double _dblImg1,
    double* _pdblReal2, double* _pdblImg2, int _iSize2,
    double* _pdblRealOut,	double* _pdblImgOut);

//Square Matrix ^ Scalar
int iPowerRealSquareMatrixByRealScalar(
    double* _pdblReal1, int _iRows1, int _iCols1,
    double _dblReal2,
    double* _pdblRealOut,	double* _pdblImgOut, int *_iComplex);

int iPowerComplexSquareMatrixByRealScalar(
    double* _pdblReal1, double* _pdblImg1, int _iRows1, int _iCols1,
    double _dblReal2,
    double* _pdblRealOut,	double* _pdblImgOut);

#endif /* __MATRIC_POWER_H__ */
