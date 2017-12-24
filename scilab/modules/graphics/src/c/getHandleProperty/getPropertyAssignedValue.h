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

/*------------------------------------------------------------------------*/
/* file: getPropertyAssignedValue.h                                       */
/* desc : a set of functions used to get the values which will be         */
/*        assigned to handles properties from the stack                   */
/*------------------------------------------------------------------------*/

#ifndef _GET_PROPERTY_ASSIGNEMENT_VALUE_H_
#define _GET_PROPERTY_ASSIGNEMENT_VALUE_H_

#include <stdlib.h> /* for size_t */
#include "sci_types.h"
#include "api_scilab.h"
#include "BOOL.h"

/*------------------------------------------------------------------------------*/
/* Basic type parameters */

/**
 * copy a double vector from the scilab stack to an int array
 * with int cast for each parameter.
 */
void copyDoubleVectorToIntFromStack(void* _pvData, int dest[], int nbElement);

/**
 * create a copy of a stringMatrix which is in the stack
 */
char ** createCopyStringMatrixFromStack(void* _pvData, int nbElement);

/**
 * @return TRUE if the given parameter is 'on', %T, 'T', 1, ...
 *         FALSE if the given parameter is 'off', %F, 'F', 0, ...
 *         NOT_A_BOOLEAN_VALUE otherwise
 */
int tryGetBooleanValueFromStack(void* _pvData, int valueType, int nbRow, int nbCol, const char* propertyName);
// with that we are sure to be nether equal to TRUE nor FALSE
#define NOT_A_BOOLEAN_VALUE (2*FALSE) - TRUE

/*------------------------------------------------------------------------------*/
/* Tlist */
typedef struct
{
    int iNbItem; /**< number of elements in the tlist */
    int iCurItem; /**< currently read element */
    int iRhs; /**< rank of the tlist within the Rhs parameters */
    int* piList ; /**< pointer of the tlist in the stack */
} AssignedList;

/**
 * get the number of element of a tlist stored in the rhs
 * @param paramNum rank of the list within the Rhs parameters
 */
int getStackListNbElement(void* _pvCtx, int _iRhs);

/**
 * create a new instance of an object used to retrieve fields of a tlist
 * stored on the stack
 * @param paramNum rank of the list within the Rhs parameters
 * @param nbElement number of element in the list
 */
AssignedList * createAssignedList(void* _pvCtx, int _iRhs, int _iNbItem);

/**
 * destroy the object used to glance through a tlist
 */
void destroyAssignedList(AssignedList * list);

/**
 * return the number of element of a tlist
 */
int getAssignedListNbElement(AssignedList * list);

/**
 * set the current element to the first
 */
void rewindAssignedList(AssignedList * list);

/**
 * Return whether the current element of the list is a double matrix or not.
 */
BOOL isListCurrentElementDoubleMatrix(void* _pvCtx, AssignedList* _pList);

/**
* Return whether the current element of the list is a string matrix or not.
*/
BOOL isListCurrentElementStringMatrix(void* _pvCtx, AssignedList* _pList);

/**
* Return whether the current element of the list is an empty matrix or not.
*/
BOOL isListCurrentElementEmptyMatrix(void* _pvCtx, AssignedList* _pList);

/**
 * retrieve a field of a tlist
 * @param[in]  list object used to retrieve elements
 * @param      rank position of the element in the list (first, second, ...)
 *             Note that is it not possible to get the properties names with this function
 * @param[out] nbRow number of row of the returned matrix
 * @param[out] nbCol number of column of the returned matrix
 */
double* getDoubleMatrixFromList(void* _pvCtx, AssignedList* _pList, int _iItem, int* _piRows, int* _piCols);

/**
* retrieve a field of a tlist
* @param[in]  list object used to retrieve elements
* @param      rank position of the element in the list (first, second, ...)
*             Note that is it not possible to get the properties names with this function
* @param[out] nbRow number of row of the returned matrix
* @param[out] nbCol number of column of the returned matrix
*/
char ** getStringMatrixFromList(void* _pvCtx, AssignedList* _pList, int _iItem, int* _piRows, int* _piCols);


/**
 * retrieve the current property of a tlist and move to the next
 * @param[in/out] list object used to retrieve elements
 * @param[out]    nbRow number of row of the returned matrix
 * @param[out]    nbCol number of column of the returned matrix
 */
double* getCurrentDoubleMatrixFromList(void* _pvCtx, AssignedList* _pList, int* _piRows, int* _piCols);

/**
* retrieve the current property of a tlist and move to the next
* @param[in/out] list object used to retrieve elements
* @param[out]    nbRow number of row of the returned matrix
* @param[out]    nbCol number of column of the returned matrix
*/
char ** getCurrentStringMatrixFromList(void* _pvCtx, AssignedList* _pList, int* _piRows, int* _piCols);

/**
 * create a copy of the current matrix in the tlist
 * @param[in/out] list object used to retrieve elements
 * @param[out]    nbRow number of row of the returned matrix or -1 if an error occurred
 * @param[out]    nbCol number of column of the returned matrix or -1 if an error occurred
 * @return the created array or NULL if the matrix is empty or an error occurred
 */
double* createCopyDoubleMatrixFromList(void* _pvCtx, AssignedList* _pList, int* _piRows, int* _piCols);

#endif /* _GET_PROPERTY_ASSIGNEMENT_VALUE_H_ */
