/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011-2011 - DIGITEO - Bruno JOFRET
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

#ifndef __FIGURE_LIST_H__
#define __FIGURE_LIST_H__

#include "BOOL.h"

/**
 * @return number of opened windows in Scilab.
 */
int sciGetNbFigure(void);

/**
 * @return the next free figure id.
 */
int getValidDefaultFigureId();

/**
 * Fill the array Ids with all the figure ids currently used by Scilab.
 * @param ids should be as long as there are figures.
 */
void sciGetFiguresId(int ids[]);

/**
 * @return TRUE if the figure with index id exists
 */
BOOL sciIsExistingFigure(int figNum);

/**
 * Register Scilab View to Graphic Controller
 */
void registerToController(void);

/**
 * Unregister Scilab View to Graphic Controller
 */
void unregisterToController(void);

/**
 * to know if there are some opened graphic windows
 */
BOOL sciHasFigures(void);

/**
 * returns the UID of window i
 * or NULL if this window does not exists
 */
int getFigureFromIndex(int figNum);

int search_path(char* _pstPath);
char* get_path(int uid);

#endif /* !__FIGURE_LIST_H__ */
