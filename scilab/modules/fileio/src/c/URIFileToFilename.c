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
/*--------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "URIFileToFilename.h"
#include "sci_malloc.h"
#include "os_string.h"
#include "strlen.h"
/*--------------------------------------------------------------------------*/
#if _MSC_VER
#define strnicmp _strnicmp
#else
#define strnicmp strncasecmp
#endif
/*--------------------------------------------------------------------------*/
#define URI_BEGIN "file://"
/*--------------------------------------------------------------------------*/
char *URIFileToFilename(char *uri)
{
    char *filename = NULL;

    if (uri)
    {
        if (isURIFile(uri))
        {
            int pos = (int) balisc_strlen(URI_BEGIN);
            filename = os_strdup(&uri[pos]);
        }
        else
        {
            filename = os_strdup(uri);
        }
    }
    return filename;
}
/*--------------------------------------------------------------------------*/
BOOL isURIFile(char *uri)
{
    BOOL bOK = FALSE;
    if (uri)
    {
        if (balisc_strlen(uri) > balisc_strlen(URI_BEGIN))
        {
            if ( strnicmp(uri, URI_BEGIN, balisc_strlen(URI_BEGIN)) == 0)
            {
                bOK = TRUE;
            }
        }
    }
    return bOK;
}
/*--------------------------------------------------------------------------*/
