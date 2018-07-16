/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Allan CORNET
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

#include <stdlib.h>
#include "freeArrayOfString.h"
#include "sci_malloc.h"

void freeArrayOfString(char **Str, int dim)
{
    freeArray((void**)Str, dim);
}

void freeArrayOfWideString(wchar_t **wcStr, int dim)
{
    freeArray((void**)wcStr, dim);
}

void freeArray(void **pArray, int dim)
{
    if (pArray)
    {
        int i = 0;
        for (i = 0; i < dim; i++)
        {
            if (pArray[i])
            {
                FREE(pArray[i]);
            }
        }
        FREE(pArray);
        pArray = NULL;
    }
}
