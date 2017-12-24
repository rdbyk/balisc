/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
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

/*------------------------------------------------------------------------*/
/* file: axesScale.h                                                      */
/* desc : Contains functions to compute scale changes in a specific       */
/*        subwindow.                                                      */
/*------------------------------------------------------------------------*/

#ifndef _AXES_SCALE_H_
#define _AXES_SCALE_H_

#include "BOOL.h"

int sciZoom2D(int iSubwinUID, const double zoomRect[4]);
int sciZoom3D(int iSubwinUID, const double zoomBox[6]);
int sciZoomRect(int iObjUID, const double zoomRect[4]);
int sciFigureZoom2D(int iFigureUID, const double zoomRect[4]);
void sciUnzoomSubwin(int iSubwinUID);
void sciUnzoomFigure(int iFigureUID);
void sciUnzoomArray(int iObjUID[], int nbSubwin);

/**
 * Update subwin size and scale if needed
 */
void updateSubwinScale(int iSubwinUID);

/**
 * Update text bounds if needed
 */
void updateTextBounds(int iSubwinUID);


BOOL checkDataBounds(int iSubwinUID, double xMin, double xMax,
                                     double yMin, double yMax, double zMin, double zMax);

#endif /* _AXES_SCALE_H_ */
