/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
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
/*--------------------------------------------------------------------------*/
#ifndef __GETFULLFILENAME_H__
#define __GETFULLFILENAME_H__

#include <wchar.h>

/**
* get full filename of a file (wide string)
* @param[in] FilenameInput can be a relative path
* @return a full filename (path expanded)
*/
wchar_t* getFullFilenameW(const wchar_t* FilenameInput);

/**
* get full filename of a file
* @param[in] FilenameInput can be a relative path
* @return a full filename (path expanded)
*/
char* getFullFilename(const char* Filename);

#endif /* __GETFULLFILENAME_H__ */
/*--------------------------------------------------------------------------*/
