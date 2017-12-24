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

#ifndef __URIFILETOFILENAME_H__
#define __URIFILETOFILENAME_H__

#include "BOOL.h"

/**
* convert URI File (file://path/filename.ext) to standard filename
* @param[in] uri : a string URI file
* @return a filename
*/
char *URIFileToFilename(char *uri);

/**
* check if it is a URIFile
* @param [in] uri : a string URI file
* @return TRUE or FALSE;
*/
BOOL isURIFile(char *uri);

#endif /* __URIFILETOFILENAME_H__ */
