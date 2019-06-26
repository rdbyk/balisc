/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "machine.h" /* bsiz */
#include "convertbase.h"
#include "sci_malloc.h"
#include "freeArrayOfPtrs.h"
#include "strlen.h"
/*--------------------------------------------------------------------------*/
#define char_a 'a'
#define char_A 'A'
#define char_z 'z'
#define char_Z 'Z'
#define char_zero '0'
#define char_nine '9'
/*--------------------------------------------------------------------------*/
double convertBase2Dec(const char *pStr, int numberbase, error_convertbase *err)
{
    double result = 0.;
    *err = ERROR_CONVERTBASE_NOK;

    if (pStr)
    {
        size_t i = 0;
        size_t len = balisc_strlen(pStr);
        for (i = 0; i < len; i++)
        {
            if ((pStr[i] >= char_zero) && (pStr[i] <= char_nine))
            {
                result = (numberbase * result) + (int)pStr[i] - char_zero;
            }
            else if ((pStr[i] >= char_A) && (pStr[i] <= char_Z))
            {
                int vTmp = (int)pStr[i] - char_A + 10;
                if (vTmp >= numberbase)
                {
                    *err = ERROR_CONVERTBASE_INVALID_REPRESENTATION;
                    return 0;
                }
                else
                {
                    result = (numberbase * result) + vTmp;
                }
            }
            else if ((pStr[i] >= char_a) && (pStr[i] <= char_z))
            {
                int vTmp = (int)pStr[i] - char_a + 10;
                if ( vTmp >= numberbase)
                {
                    *err = ERROR_CONVERTBASE_INVALID_REPRESENTATION;
                    return 0;
                }
                else
                {
                    result = (numberbase * result) + vTmp;
                }
            }
            else
            {
                return 0;
            }
        }
        *err = ERROR_CONVERTBASE_OK;
    }
    return result;
}
/*--------------------------------------------------------------------------*/
