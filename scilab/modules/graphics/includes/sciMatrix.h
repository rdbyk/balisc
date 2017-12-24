/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
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

/*----------------------------------------------------------------------------------*/
/* File    : sciMatrix.h                                                                     */
/* Desc.   : Allocation and deletion and modifications of matrices of pointers               */
/*           The matrix is stored by colmuns like in Scilab.                                 */
/*           These matrices can be used as generic matrices since they used void * pointers  */
/*----------------------------------------------------------------------------------*/

#ifndef _SCI_MATRIX_H_
#define _SCI_MATRIX_H_

/*----------------------------------------------------------------------------------*/
/**
 * a matrix on void pointers
 */
typedef struct
{
    void ** data ; /**< the data are stored in an array of void pointers */
    int nbCol   ;
    int nbRow   ;
}
sciMatrix;

sciMatrix * emptyMatrix(void);
sciMatrix * newMatrix(int nbRow, int nbCol);
void deleteMatrix(sciMatrix * mat);

#endif /* _SCI_MATRIX_H_ */
