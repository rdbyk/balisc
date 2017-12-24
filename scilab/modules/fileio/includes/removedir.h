/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Allan CORNET
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

#ifndef __REMOVEDIR_H__
#define __REMOVEDIR_H__

#include <wchar.h>
#include "BOOL.h"

/**
* Remove a directory
* @param path the directory
* @return the result of the operation
*/
BOOL removedir(char *path);

/**
* Remove a directory
* @param path the directory (wide string)
* @return the result of the operation
*/
BOOL removedirW(wchar_t *pathW);

#endif /* __REMOVEDIR_H__ */
