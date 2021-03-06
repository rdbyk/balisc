/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2011 - DIGITEO - Allan CORNET
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

#include "complex_array.h"
#include "sci_malloc.h"

complexArray *createComplexArrayEmpty(int nbSize)
{
    complexArray *pComplexArray = NULL;
    pComplexArray = (complexArray *) MALLOC(sizeof(complexArray));
    if (pComplexArray)
    {
        pComplexArray->realPart = (double *)CALLOC(nbSize, sizeof(double));
        if (pComplexArray->realPart == NULL)
        {
            FREE(pComplexArray);
            return NULL;
        }

        pComplexArray->imagPart = (double *)CALLOC(nbSize, sizeof(double));
        if (pComplexArray->imagPart == NULL)
        {
            FREE(pComplexArray->realPart);
            pComplexArray->realPart = NULL;
            FREE(pComplexArray);
            return NULL;
        }

        pComplexArray->isComplex = 1;
        pComplexArray->nbElements = nbSize;
    }
    return pComplexArray;
}

void freeComplexArray(complexArray *pComplexArray)
{
    if (pComplexArray)
    {
        if (pComplexArray->realPart)
        {
            FREE(pComplexArray->realPart);
            pComplexArray->realPart = NULL;
        }

        if (pComplexArray->imagPart)
        {
            FREE(pComplexArray->imagPart);
            pComplexArray->imagPart = NULL;
        }
        pComplexArray->isComplex = 0;
        pComplexArray->nbElements = 0;

        FREE(pComplexArray);
        pComplexArray = NULL;
    }
}

int cleanImagPartComplexArray(complexArray *pComplexArray)
{
    if (pComplexArray)
    {
        if (pComplexArray->imagPart)
        {
            int i = 0;

            pComplexArray->isComplex = 0;

            for (i = 0; i < pComplexArray->nbElements; i++)
            {
                if (pComplexArray->imagPart[i] != 0)
                {
                    pComplexArray->isComplex = 1;
                    break;
                }
            }
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
