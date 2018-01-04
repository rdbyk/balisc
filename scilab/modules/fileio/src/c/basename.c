/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
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
#include "basename.h"
#include "sci_malloc.h"
#include "expandPathVariable.h"
#include "splitpath.h"
#include "charEncoding.h"
/*--------------------------------------------------------------------------*/
wchar_t *basenameW(wchar_t *wcfullfilename, BOOL bExpand)
{
    wchar_t *basename_str = NULL;

    if (wcfullfilename)
    {
        wchar_t *expandedPath = expandPathVariableW(wcfullfilename);

        if (expandedPath)
        {
            size_t size_expandedPath = sizeof(wchar_t) * (wcslen(expandedPath) + 1);
            
            wchar_t* wcname = (wchar_t*)MALLOC(size_expandedPath);
            wchar_t* wcext = (wchar_t*)MALLOC(size_expandedPath);
            
            /* FIXME: cf. #249, #269 */
            splitpathW(expandedPath, bExpand, NULL, NULL, wcname, wcext);

            if (wcname)
            {
                basename_str = wcname;
            }

            if (wcext)
            {
                FREE(wcext);
            }

            FREE(expandedPath);
        }
    }

    return basename_str;
}
