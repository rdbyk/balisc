/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 1998-2001 - ENPC - Jean-Philippe Chancelier
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

/*------------------------------------------------------------------------
 *    Graphic library
 --------------------------------------------------------------------------*/

#include "math_graphics.h"

/*
 * we use spConfig.h for machine constants
 * XXX : spConfig should be merged and unified
 *       with other machine constant scilab code
 */

#define spINSIDE_SPARSE
#include "../../sparse/includes/spConfig.h"

double Mini(const double vect[], int n)
{
    int i = 0;
    double vmin = LARGEST_REAL;
    for (i = 0 ; i < n ; i++)
    {
        /*    if (isinf(vect[i])== 0 && isnan(vect[i])==0 && vect[i] < vmin)  */
        if (finite(vect[i]) == 1 && vect[i] < vmin)
        {
            vmin = vect[i];
        }
    }

    return vmin;
}

double Maxi(const double vect[], int n)
{
    int i = 0;
    double maxi = - LARGEST_REAL;
    for (i = 0 ; i < n ; i++)
    {
        /* if (isinf(vect[i])== 0 && isnan(vect[i])==0 && vect[i] > maxi) */
        if (finite(vect[i]) == 1 && vect[i] > maxi)
        {
            maxi = vect[i];
        }
    }

    return maxi;
}

void MiniMaxi(const double vect[], int n, double * const min, double * const max)
{
    int i = 0;
    double _min = LARGEST_REAL;
    double _max = -LARGEST_REAL;
    for (; i < n ; i++)
    {
        /*    if ( isinf(vect[i])== 0 && isnan(vect[i])==0 && vect[i] < vmin)  */
        if (finite(vect[i]) == 1)
        {
            if (vect[i] < _min)
            {
                _min = vect[i];
            }
            if (vect[i] > _max)
            {
                _max = vect[i];
            }
        }
    }

    *min = _min;
    *max = _max;
}
/*----------------------------------------------------------------------------*/
