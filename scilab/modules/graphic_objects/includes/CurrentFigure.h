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

#ifndef __CURRENT_FIGURE_H__
#define __CURRENT_FIGURE_H__

/**
 * Returns UID of the current selected figure.
 */
int getCurrentFigure(void);

/**
 * Modify the current figure if needed.
 */
void setCurrentFigure(int iUID);

/**
 * To know if a figure is the selected one.
 */
BOOL isCurrentFigure(int iUID);

#endif /* !__CURRENT_FIGURE_H__ */
