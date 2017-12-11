/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 1998 - 2000 - ENPC - Jean-Philipe Chancelier
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

#ifndef __SCIMATH_H__
#define __SCIMATH_H__

#include <stdlib.h>
#include "dynlib_graphics.h"
#include "BOOL.h"
#include "core_math.h"

#if (defined(sun) || defined(SYSV))
#include <ieeefp.h>
#endif

#if defined(_MSC_VER)
#define M_PI 3.14159265358979323846
#else
#if defined(HAVE_VALUES_H)
#include <values.h>
#else
#if defined(HAVE_LIMITS_H)
#include <limits.h>
#endif
#endif
#endif

GRAPHICS_IMPEXP double Mini(const double vect[], int n);
GRAPHICS_IMPEXP double Maxi(const double vect[], int n);
GRAPHICS_IMPEXP void MiniMaxi(const double vect[], int n, double * const min, double * const max);

#endif /* SCI_MATH.HG */

