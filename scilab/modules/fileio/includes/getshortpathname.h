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

#ifndef __GETSHORTPATHNAME_H__
#define __GETSHORTPATHNAME_H__

#include "machine.h" /* C2F */
#include "BOOL.h"
#include <wchar.h>

/**
* Retrieves the short path form of the specified path
* @param[in] long path name
* @param[out] TRUE if conversion is ok
* @return short path name
* on Linux returns same path name
* used for Windows
*/
char *getshortpathname(const char *longpathname, BOOL *convertok);
wchar_t* getshortpathnameW(const wchar_t* _pwstLongPathName, BOOL* _pbOK);

#endif /* __GETSHORTPATHNAME_H__ */
