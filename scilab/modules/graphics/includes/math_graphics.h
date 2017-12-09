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

/* prototypes */

/*----------------------------------------------------------------------------*/
/************************************************************************/
/* 2D algorithms                                                        */
/************************************************************************/
/* perform the rotation of point from to point dest with angle in radian  */
GRAPHICS_IMPEXP void rotate2D(double from[2], double center[2], double angle, double dest[2]);

/* perform the rotation of point from to point to. */
/* the angle is directly given with its sine and cosine for speed */
GRAPHICS_IMPEXP void rotate2Dim(double from[2]   ,
                                double center[2] ,
                                double cosAngle  ,
                                double sinAngle  ,
                                double dest[2]);

/* perform the translation of point from to point dest with vector trans */
GRAPHICS_IMPEXP void translate2D(double from[2], double trans[2], double dest[2]);

/* perform the translation of point from to point dest with vector trans given in pixels.*/
GRAPHICS_IMPEXP void iTranslate2D(int from[2], int trans[2], int dest[2]);

/**
 * Normalize a 2d vector.
 */
GRAPHICS_IMPEXP void normalize2d(double vect[2]);

/**
 * Normalize a 2d vector in pixels coordinates.
 */
GRAPHICS_IMPEXP void iNormalize2d(int vect[2]);

/**
 * Perform the subtraction of vect1 and vect2 and store it in res
 */
GRAPHICS_IMPEXP void vectSubstract2D(const double vect1[2], const double vect2[], double res[2]);

/**
 * subtraction of two vector
 * @param res result of v1 + v2
 */
GRAPHICS_IMPEXP void vectAdd2D(const double v1[2], const double v2[2], double res[2]);

/**
 * Multiply a vector by a scalar
 * @param res scalar.v
 */
GRAPHICS_IMPEXP void scalarMult2D(const double v[2], const double scalar, double res[2]);


/**
 * Compute whether the point lies within the triangle defined by A, B and C
 */
GRAPHICS_IMPEXP BOOL isPointInTriangle(const double point[2], const double a[2],
                                       const double b[2], const double c[2]);

/**
 * Compute whether p1 and p2 are on the same side of line (A,B).
 */
GRAPHICS_IMPEXP BOOL areOnSameSideOfLine(const double p1[2], const double p2[2],
        const double a[2], const double b[2]);

/************************************************************************/
/* 3D algorithms                                                        */
/************************************************************************/

/**
 * Cross product of two vector
 * @param res v1^v2
 */
GRAPHICS_IMPEXP void crossProduct(const double v1[3], const double v2[3], double res[3]);

/**
 * subtraction of two vector
 * @param res result of v1 - v2
 */
GRAPHICS_IMPEXP void vectSubstract3D(const double v1[3], const double v2[3], double res[3]);

/**
 * subtraction of two vector
 * @param res result of v1 + v2
 */
GRAPHICS_IMPEXP void vectAdd3D(const double v1[3], const double v2[3], double res[3]);

/**
 * Multiply a vector by a scalar
 * @param res scalar.v
 */
GRAPHICS_IMPEXP void scalarMult3D(const double v[3], double scalar, double res[3]);

/**
 * Normalize a 3D vector
 */
GRAPHICS_IMPEXP void normalize3D(double vect[3]);

/**
 * Set a 4x4 matrix to identity.
 */
GRAPHICS_IMPEXP void setToIdentity(double mat4D[4][4]);

/**
 * Compute the product mat4D*vect3D and store the result in res.
 */
GRAPHICS_IMPEXP void mat4DMult(const double mat4D[4][4], const double vect3D[3], double res[3]);

#endif /* SCI_MATH.HG */

