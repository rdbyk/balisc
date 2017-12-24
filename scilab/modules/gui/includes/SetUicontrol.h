/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2014 - Scilab Enterprises - Antoine ELIAS
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

#ifndef __SET_UICONTROL_H__
#define __SET_UICONTROL_H__

#include <stdio.h>
#include "BOOL.h"
#include "returnProperty.h"
#include "setHandleProperty.h"
#include "Scierror.h"
#include "sciprint.h"
#include "localization.h"
#include "SetPropertyStatus.h"
#include "sci_types.h"
#include "setGraphicObjectProperty.h"
#include "getGraphicObjectProperty.h"
#include "graphicObjectProperties.h"
#include "checkColorRange.h"
#include "getPropertyAssignedValue.h"
#include "os_string.h"

int SetUicontrolIcon(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolBackgroundColor(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolFontAngle(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolFontName(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolFontSize(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolFontUnits(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolFontWeight(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolHorizontalAlignment(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolListboxTop(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolMax(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolMin(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolPosition(int iObjUID, void* pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolRelief(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolSliderStep(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolString(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol ) ;
int SetUicontrolTooltipString(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol ) ;
int SetUicontrolUnits(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolValue(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUicontrolVerticalAlignment(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUimenuChecked(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUimenuLabel(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetUiobjectEnable(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol ) ;
int SetUiobjectForegroundColor(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
int SetConsoleShowHiddenHandles(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol ) ;
int SetConsoleShowHiddenProperties(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol ) ;
int SetConsoleUseDeprecatedLF(void* _pvCtx, int iObjUID, void* _pvData, int valueType, int nbRow, int nbCol);
const char *IntToStyle(int _iStyle);

#endif /* __SET_UICONTROL_H__ */
