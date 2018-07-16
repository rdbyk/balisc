/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
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

/*----------------------------------------------------------------------------------*/
/* File    : sciMatrix.c                                                                     */
/* Desc.   : Allocation and deletion and modifications of matrices of pointers               */
/*           The matrix is stored by colmuns like in Scilab.                                 */
/*           These matrices acan be used as generic matrices since they used void * pointers */
/*----------------------------------------------------------------------------------*/

#include <string.h>
#include "sciMatrix.h"
#include "sci_malloc.h"

sciMatrix* newMatrix(int nbRow, int nbCol)
{
    int i = 0;

    /* create the matrix */
    sciMatrix* newMat = MALLOC(sizeof(sciMatrix));

    if (newMat == NULL)
    {
        return NULL ;
    }

    /* allocate the data */
    newMat->data  = CALLOC((nbRow * nbCol), sizeof(void*));
    newMat->nbRow = nbRow;
    newMat->nbCol = nbCol;

    return newMat;
}

void deleteMatrix(sciMatrix * mat)
{
    int i = 0;

    for (i = 0; i < mat->nbRow * mat->nbCol; ++i)
    {
        FREE(mat->data[i]);
    }

    FREE(mat->data);
    FREE(mat);
    mat = NULL;
}
