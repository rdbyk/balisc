/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - DIGITEO - Antoine ELIAS
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

#ifndef __TRANSPOSE_H__
#define __TRANSPOSE_H__

#include "doublecomplex.h"

void vTransposeRealMatrix(
    double *_pdblRealIn,
    int _iRowsIn, int _iColsIn,
    double *_pdblRealOut);

void vTransposeComplexMatrix(
    double *_pdblRealIn, double *_pdblImgIn,
    int _iRowsIn, int _iColsIn,
    double *_pdblRealOut, double *_pdblImgOut, int _iConjugate);

void vTransposeDoubleComplexMatrix(
    doublecomplex *_poIn,
    int _iRowsIn, int _iColsIn,
    doublecomplex *_poOut, int _iConjugate);

void vPretransposeRealMatrix(
    double *_pdblRealIn,
    int _iRowsIn, int _iColsIn,
    double *_pdblRealOut);

void vPretransposeComplexMatrix(
    double *_pdblRealIn, double *_pdblImgIn,
    int _iRowsIn, int _iColsIn,
    double *_pdblRealOut, double *_pdblImgOut);

#endif /* __TRANSPOSE_H__ */
