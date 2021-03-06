/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008-2008 - INRIA - Antoine ELIAS <antoine.elias@scilab.org>
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

#include "matrix_transpose.h"

void vTransposeRealMatrix(double *_pdblRealIn, int _iRowsIn, int _iColsIn, double *_pdblRealOut)
{
    int iIndex = 0;
    for (iIndex = 0 ; iIndex < _iRowsIn * _iColsIn ; iIndex++)
    {
        int iNewCoord = iIndex % _iRowsIn * _iColsIn + (iIndex / _iRowsIn);
        _pdblRealOut[iNewCoord] = _pdblRealIn[iIndex];
    }
}

void vTransposeComplexMatrix(double *_pdblRealIn, double *_pdblImgIn, int _iRowsIn, int _iColsIn, double *_pdblRealOut, double *_pdblImgOut, int _iConjugate)
{
    int iIndex = 0;
    for (iIndex = 0 ; iIndex < _iRowsIn * _iColsIn ; iIndex++)
    {
        int iNewCoord = iIndex % _iRowsIn * _iColsIn + (iIndex / _iRowsIn);

        _pdblRealOut[iNewCoord] = _pdblRealIn[iIndex];

        if (_iConjugate == 0)
        {
            _pdblImgOut[iNewCoord] = _pdblImgIn[iIndex];
        }
        else
        {
            _pdblImgOut[iNewCoord] = -_pdblImgIn[iIndex];
        }
    }
}

void vTransposeDoubleComplexMatrix(doublecomplex *_poIn, int _iRowsIn, int _iColsIn, doublecomplex *_poOut, int _iConjugate)
{
    int iIndex = 0;
    for (iIndex = 0 ; iIndex < _iRowsIn * _iColsIn ; iIndex++)
    {
        int iNewCoord = iIndex % _iRowsIn * _iColsIn + (iIndex / _iRowsIn);

        _poOut[iNewCoord].r = _poIn[iIndex].r;

        if (_iConjugate == 0)
        {
            _poOut[iNewCoord].i = _poIn[iIndex].i;
        }
        else
        {
            _poOut[iNewCoord].i = -_poIn[iIndex].i;
        }
    }
}
