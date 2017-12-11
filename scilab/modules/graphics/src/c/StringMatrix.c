/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
 *
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

/*----------------------------------------------------------------------------------*/
/* COPYRIGHT INRIA 2006                                                                      */
/* Desc.   : Allocation and deletion and modifications of matrices of strings.               */
/*           The matrix is stored by colmuns like in Scilab                                  */
/*----------------------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include "StringMatrix.h"
#include "sci_malloc.h"
#include "os_string.h"

/*----------------------------------------------------------------------------------*/
char ** getStrMatData(const StringMatrix * mat)
{
    return (char **) mat->data;
}
/*----------------------------------------------------------------------------------*/
void copyStrMatElement(StringMatrix * mat, int row, int col, const char * copyStr)
{
    char * changedString = (char *) mat->data[row + col * mat->nbRow] ; /* for speed */
    if (changedString != NULL)
    {
        FREE(changedString);
    }
    changedString = os_strdup(copyStr);
    mat->data[row + col * mat->nbRow] = changedString;
}
/*----------------------------------------------------------------------------------*/
