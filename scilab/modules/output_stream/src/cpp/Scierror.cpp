/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA -
 * Copyright (C) DIGITEO - 2010 - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "configvariable.hxx"

extern "C"
{
#include <string.h>
#include <stdio.h>
#include "Scierror.h"
#include "sci_malloc.h"
#include "charEncoding.h"
#include "lasterror.h"
#include "errmsgs.h"
}

int  Scierror(int iv, ...)
{
    int retval = 0;
    char* stptr = NULL;
    va_list ap;

    char *errmsg = ErrorMessageByNumber(iv);

    va_start(ap, iv);

    if (errmsg)
    {
        const ConfigVariable::WhereVector& where = ConfigVariable::getWhere();

        retval = vasprintf(&stptr, errmsg, ap);

        if (retval >= 0 && where.size() > 0)
        {
            char* fname = wide_string_to_UTF8(where.rbegin()->call->getName().c_str());
            char* tmp;
            retval = asprintf(&tmp, "%s: %s", fname, stptr);
            FREE(fname);
            FREE(stptr);
            stptr = tmp;
        }
    }
    else
    {
        const char* fmt = va_arg(ap, const char*);
        retval = vasprintf(&stptr, fmt, ap);
    }

    va_end(ap);

    if (retval < 0)
    {
        setLastError(iv, NULL, 0, NULL);
    }
    else
    {
        wchar_t* pwstError = to_wide_string(stptr);
        FREE(stptr);
        setLastError(iv, pwstError, 0, NULL);
        FREE(pwstError);
    }

    return retval;
}
