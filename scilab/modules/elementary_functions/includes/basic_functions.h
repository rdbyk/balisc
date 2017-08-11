/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - INRIA - Antoine ELIAS
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

#ifndef __BASIC_FUNCTION__
#define __BASIC_FUNCTION__

#include <stdlib.h>
#include <math.h>

#include "dynlib_elementary_functions.h"
#include "BOOL.h"
#include "elem_common.h"

#include "log.h"

#define BY_ROWS			1
#define BY_COLS			2
#define BY_ALL			0
#define	BY_MTLB			-1

ELEMENTARY_FUNCTIONS_IMPEXP double wasums(int _iNbElem, double* _pdblReal, double* _pdblImg);

ELEMENTARY_FUNCTIONS_IMPEXP void vDadd(int _iNbElem, double* _pdblIn1, double* _pdblIn2, int _iIncIn1, int _iIncIn2, double* _pdblOut);
ELEMENTARY_FUNCTIONS_IMPEXP void vDless(int _iNbElem, double* _pdblIn1, double* _pdblIn2, int _iIncIn1, int _iIncIn2, double* _pdblOut);
ELEMENTARY_FUNCTIONS_IMPEXP void vDset(int _iNbElem, double _dblVal, double* _pdblIn, int _iInc);
ELEMENTARY_FUNCTIONS_IMPEXP void vDsearchC(double *_pdblX, int _iNbElemX, double *_pdblVal, int _iNbElemVal, double* _pdblInd, double *_pdblOcc, double *_pdblInfo);
ELEMENTARY_FUNCTIONS_IMPEXP void vDsearchD(double *_pdblX, int _iNbElemX, double *_pdblVal, int _iNbElemVal, double* _pdblInd, double *_pdblOcc, double *_pdblInfo);

ELEMENTARY_FUNCTIONS_IMPEXP double durands(int *_iVal);
ELEMENTARY_FUNCTIONS_IMPEXP int nint(double _iVal);

ELEMENTARY_FUNCTIONS_IMPEXP void franck_matrix(int _iSize, double *_pData);
ELEMENTARY_FUNCTIONS_IMPEXP void hilb_matrix(int _iSize, double *_pData);
ELEMENTARY_FUNCTIONS_IMPEXP void magic_matrix(int _iSize, double *_pData);

#endif //__BASIC_FUNCTION__
