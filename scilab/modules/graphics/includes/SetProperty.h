/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2001 - 2002 - INRIA - Matthhieu Philippe
 * Copyright (C) 2002 - 2004 - INRIA - Djalel Abdemouche
 * Copyright (C) 2004 - 2006 - INRIA - Fabrice Leray
 * Copyright (C) 2005 - INRIA - Jean-Baptiste Silvy
 * Copyright (C) 2010 - Paul Griffiths
 * Copyright (C) 2011 - DIGITEO - Bruno JOFRET
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

/*------------------------------------------------------------------------
 *    Graphic library
 *    -This file contains all functions used to SET the properties of graphics
 *    objects.
 *    - there are two kinds of functions : the sciInit*** which only set an object
 *      property and sciSet*** which do the same work but check before if it is
 *      necessary to do so.
 *    - The returning status of each functions is as follow :
 *      0 for correct execution, 1 if no change was made
 *      and -1 if an error occurred.
 --------------------------------------------------------------------------*/

#ifndef __SCI_SET_PROPERTY__
#define __SCI_SET_PROPERTY__

#include "BOOL.h"

int sciSetLineWidth (int iObj, double linewidth) ;  /* SET */
int sciSetLineStyle (int iObj, int linestyle) ; /* SET */
int sciSetMarkSize (int iObj, int *markSizes, int numMarkSizes); /* SET */

/* Text Functions */
int sciSetText (int iObj, char ** text, int nbRow, int nbCol) ; /* SET */

/* GMODE */
int sciSetDefaultValues (void); /* SET */


/* Window Functions */
int sciSetSelectedSubWin (int iSubwinobj); /* SET */
int sciSetPoint(int iObj, double *tab, int *numrow, int *numcol); /* SET */
BOOL sciCheckColorIndex(int iObj, int colorIndex);
int sciSetMarkOffset(int iObjUID, int offset);
int sciSetMarkStride(int iObjUID, int stride);

#endif /* __SCI_SET_PROPERTY__ */
