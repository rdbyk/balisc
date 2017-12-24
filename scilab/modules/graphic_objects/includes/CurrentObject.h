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

#ifndef __CURRENT_OBJECT_H__
#define __CURRENT_OBJECT_H__

#include "BOOL.h"

/**
 * Returns UID of the current selected object.
 */
int getCurrentObject(void);

/**
 * Modify the current object if needed.
 */
void setCurrentObject(int iUID);

/**
 * To know if an object is the selected one.
 */
BOOL isCurrentObject(int iUID);

/**
 * get parent object
 */
int getParentObject(int iUID);
void setParentObject(int iUID, int iParent);

#endif /* !__CURRENT_OBJECT_H__ */
