/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Antoine Elias
 * Copyright (C) 2011 - DIGITEO - Cedric Delamarre
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "matrix_kronecker.h"
#include "elem_common.h"

#include <stdio.h>

// Real .*. Real
void vKronR(double* _pdblDataIn1, int _iIncIn1, int _iRowsIn1, int _iColsIn1,
            double* _pdblDataIn2, int _iIncIn2, int _iRowsIn2, int _iColsIn2,
            double* _pdblDataOut, int _iIncOut)
{
    int iSize1 = _iRowsIn1 * _iColsIn1;
    int iSize2 = _iRowsIn2 * _iColsIn2;

    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int idx = 0;

    for (i = 0 ; i < iSize1 ; i += _iRowsIn1)
    {
        int i2 = i + _iRowsIn1;
        for (j = 0 ; j < iSize2 ; j += _iRowsIn2)
        {
            int j2 = j + _iRowsIn2;
            for (k = i ; k < i2 ; k++)
            {
                //double c = _pdblDataIn1[k];
                for (l = j; l < j2; l++, idx++)
                {
                    _pdblDataOut[idx] = _pdblDataIn1[k] * _pdblDataIn2[l];
                }
            }
        }
    }
}

// Complex .*. Complex
void vKronC(double* _pdblRealIn1, double* _pdblImgIn1, int _iIncIn1, int _iRowsIn1, int _iColsIn1,
            double* _pdblRealIn2, double* _pdblImgIn2, int _iIncIn2, int _iRowsIn2, int _iColsIn2,
            double* _pdblRealOut, double* _pdblImgOut, int _iIncOut)
{
    int iSize1 = _iRowsIn1 * _iColsIn1;
    int iSize2 = _iRowsIn2 * _iColsIn2;

    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int idx = 0;

    for (i = 0 ; i < iSize1 ; i += _iRowsIn1)
    {
        int i2 = i + _iRowsIn1;
        for (j = 0 ; j < iSize2 ; j += _iRowsIn2)
        {
            int j2 = j + _iRowsIn2;
            for (k = i ; k < i2 ; k++)
            {
                //double c = _pdblDataIn1[k];
                for (l = j; l < j2; l++, idx++)
                {
                    _pdblRealOut[idx] = _pdblRealIn1[k] * _pdblRealIn2[l] - _pdblImgIn1[k] * _pdblImgIn2[l];
                    _pdblImgOut[idx] = _pdblRealIn1[k] * _pdblImgIn2[l] + _pdblImgIn1[k] * _pdblRealIn2[l];
                }
            }
        }
    }
}

// convert : a => 1 ./ a
int conv_real_input(double* _pdblData, int _iSize)
{
    int div_by_zero = 0;

    int i;
    for (i = 0 ; i < _iSize ; i++)
    {
        div_by_zero = _pdblData[0] == 0.0;
        _pdblData[i] = 1.0 / _pdblData[i];
    }

    if (div_by_zero)
    {
        int mode = getieee();

        if (mode == 2)
        {
            return 0; // ok
        }
        else if (mode == 1)
        {
            return 2; // warning
        }
        else // mode = 0
        {
            return 1; // error
        }
    }
    else
    {
        return 0;
    }
}

int conv_img_input(double* _pdblReal, double* _pdblImg, int _iSize)
{
    int div_by_zero = 0;

    int i;
    for (i = 0 ; i < _iSize ; i++)
    {
        double dblR = _pdblReal[i];
        double dblI = _pdblImg[i];
        double dblTemp	= dblR * dblR + dblI * dblI;
        double dblTempInv = 1.0 / dblTemp;
        div_by_zero = dblTemp == 0.0;
        _pdblReal[i] = _pdblReal[i]	* dblTempInv;
        _pdblImg[i] = - _pdblImg[i] * dblTempInv;
    }

    if (div_by_zero)
    {
        int mode = getieee();

        if (mode == 2)
        {
            return 0; // ok
        }
        else if (mode == 1)
        {
            return 2; // warning
        }
        else // mode = 0
        {
            return 1; // error
        }
    }
    else
    {
        return 0;
    }
}
