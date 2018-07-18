/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Fabrice Leray
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

/*------------------------------------------------------------------------*/
/* file: BasicAlgos.h                                                     */
/* desc : Several basic algorithms which can be used in several places in */
/*        the code.                                                       */
/*------------------------------------------------------------------------*/

#ifndef _BASIC_ALGOS_H_
#define _BASIC_ALGOS_H_

/**
 * Find the strictly positive minimum value of an array of double.
 * @param[in] x array of size n.
 * @return The strictly posistive minimum of x if exists, a negative value otherwise
 */
double sciFindStPosMin(const double x[], int n);

/**
 * check the strict monotony of a vector
 * @return  1 if the vector is increasing or constant
 *         -1 if decreasing and not constant
 *          0 if not monotonous
 * @param nbElement must be greater than 2.
 */
int checkMonotony(const double vector[], int nbElement);

#endif /* _BASIC_ALGOS_H_ */
