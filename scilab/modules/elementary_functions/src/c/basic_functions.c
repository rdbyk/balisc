/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - DIGITEO - Antoine ELIAS
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
#include "basic_functions.h"

/*absolute complex sum*/
double wasums(int _iNbElem, double* _pdblReal, double* _pdblImg)
{
    double dblRetVal = 0;
    int iIndex		= 0;
    int iOne		= 1;

    dblRetVal	= C2F(dasum)(&_iNbElem, _pdblReal, &iOne);
    dblRetVal	+= C2F(dasum)(&_iNbElem, _pdblImg, &iOne);

    return dblRetVal;
}

/*memset on vector*/
void vDset(int _iNbElem, double _dblVal, double* _pdblIn, int _iInc)
{
    int iIndex = 0;
    int iIndex2 = 0;
    if (_iInc < 0 )
    {
        iIndex2 = (-_iNbElem + 1) * _iInc + 1;
    }

    for (iIndex = 0 ; iIndex < _iNbElem ; iIndex++)
    {
        _pdblIn[iIndex2] = _dblVal;
        iIndex2 += _iInc;
    }
}
