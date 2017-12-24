/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Allan CORNET
 * Copyright (C) 2012 - Digiteo - Cedric Delamarre
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
/*--------------------------------------------------------------------------*/
#include "elem_common.h"
/*--------------------------------------------------------------------------*/

#if _LCC_ & FORDLL
#define IMPORT_STRUCT __declspec (dllimport)
#else
#ifdef FORDLL
#define IMPORT_STRUCT extern  __declspec (dllimport)
#else
#define IMPORT_STRUCT extern
#endif
#endif

/* csiz used for character coding */
#define csiz 63

/* bsiz size of internal chain buf */
#define bsiz 4096

#ifdef _MSC_VER
/* BUG 3863 */
/* forces to define C2F(dcoeff) only once */
typedef struct
{
    double c[41];
    int ndng;
} DCOEFF_struct;

DCOEFF_struct C2F(dcoeff);

#endif

double dblGetMatrixInfiniteNorm(double *_pdblReal, double *_pdblImg, int _iRows, int _iCols);

int dexpms2(double *_pdblReal, double *_pdblReturnReal, int _iLeadDim);

int zexpms2(double *_pdblReal, double *_pdblImg,
                                        double *_pdblReturnReal, double *_pdblReturnImg,
                                        int _iLeadDim);
