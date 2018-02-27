/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - INRIA - Antoine ELIAS
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

#ifndef __BASIC_FUNCTION__
#define __BASIC_FUNCTION__

#include <stdlib.h>
#include <math.h>

#include "BOOL.h"
#include "elem_common.h"

double wasums(int _iNbElem, double* _pdblReal, double* _pdblImg);

void vDset(int _iNbElem, double _dblVal, double* _pdblIn, int _iInc);
void vDsearchC(double *_pdblX, int _iNbElemX, double *_pdblVal, int _iNbElemVal, double* _pdblInd, double *_pdblOcc, double *_pdblInfo);
void vDsearchD(double *_pdblX, int _iNbElemX, double *_pdblVal, int _iNbElemVal, double* _pdblInd, double *_pdblOcc, double *_pdblInfo);

void franck_matrix(int _iSize, double *_pData);
void hilb_matrix(int _iSize, double *_pData);
void magic_matrix(int _iSize, double *_pData);

#endif //__BASIC_FUNCTION__
