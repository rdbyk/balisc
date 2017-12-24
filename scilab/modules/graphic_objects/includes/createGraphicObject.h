/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Bruno JOFRET
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

#ifndef __CREATEGRAPHICOBJECT_H__
#define __CREATEGRAPHICOBJECT_H__

#include "BOOL.h"

/*
** Ask Controller to create a graphic object
** of the given _sType.
*/
int createGraphicObject(int _iType);

/*
** Ask Controller to clone a graphic object
** referenced the given _sId.
*/
int cloneGraphicObject(int iId);

/*
** Ask Controller to create a data object
** referenced by the given _sId and of the given _sType
*/
int createDataObject(int iId, int _iType);

/*
** Ask Controller to create a figure menubar
** referenced by the given _sFigureId and of the given _sType
*/
void buildFigureMenuBar(int iFigureId);

int cloneGraphicContext(int iSourceIdentifier, int iDestIdentifier);
int cloneFontContext(int iSourceIdentifier, int iDestIdentifier);

BOOL isAxesRedrawing(int iSubWin);
void cloneMenus(int iModel, int iNewParent);
int cloneAxesModel(int iParent);

int createHiddenLabel(int iParent);
int createLabel(int iParent, int type);
int createNewFigureWithAxes();
int createFigure(int _bDockable, int _iMenubarType, int _iToolbarType, int _bDefaultAxes, int _bVisible);
int createSubWin(int iParent);
int createText(int iParentsubwinUID, char** text, int nbRow, int nbCol, double x, double y, BOOL autoSize, double* userSize, int  centerPos, int *foreground, int *background, BOOL isboxed, BOOL isline, BOOL isfilled, int align);
int createRect(int iParentsubwinUID, double x, double y, double height, double width, int foreground, int background, int isfilled, int isline);
int createArc(int parent, double x, double y, double h, double w, double start, double end, int* foreground, int* background, BOOL filled, BOOL line);
int createAxis(int parent, int dir, int tics, double* vx, int nx, double* vy, int ny, int subint, char* format, int fontSize, int textColor, int ticsColor, BOOL seg);
int createCompound(int parent, int* children, int childrenCount);
int createCompoundSeq(int parent, int childrenCount);
int createFec(int parent, double* zminmax, int zminmaxsize, int* colminmax, int colminmaxSize, int* colout, int coloutSize, BOOL with_mesh);
int createGrayplot(int parent, int type, double* pvecx, int pvecxSize, int n1, int n2);
int createPolyline(int parent, BOOL closed, int plot, int *foreground, int* background, int backgroundSize,
        int* mark_style, int* mark_foreground, int* mark_background, BOOL isline, BOOL isfilled, BOOL ismark, BOOL isinterp);
int createLegend(int parent, char** text, int iTextSize, int* handles, int iHandlesSize);
int createSegs(int parent, double* vx, int vxSize, double* vy, int vySize, double* vz, int vzSize, int* style, int styleSize, double arsize);
int createChamp(int parent, double* vx, int vxSize, double* vy, int vySize, double* vfx, int vfxSize, double* vfy, int vfySize, double arsize, BOOL typeofchamp);
int createSurface(int parent, int typeof3d, int colorFlag, int colorMode);
int createLight(int parent, int type, BOOL visible, double* pos, double* dir, double* ambient, double* diffuse, double* specular);

void initSubWinTo3d(int subwin, char* legend, int* flag, double alpha, double theta,
        double* ebox, double* x, int xSize, double* y, int ySize, double* z, int zSize);

int xmlload(char* xmlfile);
int xmldomload(char* xmlfile);
char* xmlsave(int id, char* xmlfile, BOOL isReverse);

#endif /* !__CREATEGRAPHICOBJECT_H__ */
