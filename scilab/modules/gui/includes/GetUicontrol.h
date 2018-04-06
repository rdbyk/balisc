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

#ifndef __GET_UICONTROL_H__
#define __GET_UICONTROL_H__

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

void* GetUicontrolIcon(void* _pvCtx, int iObjUID);
void* GetUicontrolBackgroundColor(void* _pvCtx, int iObjUID);
void* GetUicontrolFontAngle(void* _pvCtx, int iObjUID);
void* GetUicontrolFontName(void* _pvCtx, int iObjUID);
void* GetUicontrolFontSize(void* _pvCtx, int iObjUID);
void* GetUicontrolFontUnits(void* _pvCtx, int iObjUID);
void* GetUicontrolFontWeight(void* _pvCtx, int iObjUID);
void* GetUicontrolHorizontalAlignment(void* _pvCtx, int iObjUID);
void* GetUicontrolListboxTop(void* _pvCtx, int iObjUID);
void* GetUicontrolMax(void* _pvCtx, int iObjUID);
void* GetUicontrolMin(void* _pvCtx, int iObjUID);
void* GetUicontrolPosition(void* _pvCtx, int iObjUID);
void* GetUicontrolPosition(void* _pvCtx, int iObjUID);
void* GetUicontrolSliderStep(void* _pvCtx, int iObjUID);
void* GetUicontrolSnapToTicks(void* _pvCtx, int iObjUID);
void* GetUicontrolString(void* _pvCtx, int iObjUID);
void* GetUicontrolStyle(void* _pvCtx, int iObjUID);
void* GetUicontrolTooltipString(void* _pvCtx, int iObjUID);
void* GetUicontrolUnits(void* _pvCtx, int iObjUID);
void* GetUicontrolValue(void* _pvCtx, int iObjUID);
void* GetUicontrolVerticalAlignment(void* _pvCtx, int iObjUID);
void* GetUimenuChecked(void* _pvCtx, int iObjUID);
void* GetUimenuLabel(void* _pvCtx, int iObjUID);
void* GetUiobjectEnable(void* _pvCtx, int iObjUID);
void* GetUiobjectForegroundColor(void* _pvCtx, int iObjUID);
void* GetConsoleShowHiddenHandles(void* _pvCtx, int iObjUID);
void* GetConsoleShowHiddenProperties(void* _pvCtx, int iObjUID);
void* GetUicontrolRelief(void* _pvCtx, int iObjUID);
void* GetConsoleUseDeprecatedLF(void* _pvCtx, int iObjUID);
void* GetUicontrolTooltipString(void* _pvCtx, int iObjUID);
const char *IntToStyle(int _iStyle);

#endif /* __GET_UICONTROL_H__ */
