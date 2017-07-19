/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Manuel Juliachs
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

#ifndef DECOMPOSITION_UTILS_HXX
#define DECOMPOSITION_UTILS_HXX

extern "C"
{
#include <math.h>
#include <float.h>
#ifdef _MSC_VER
#define isnan _isnan
    // isinf(x)
    // | +%inf -> 1
    // | -%inf -> -1
    // | _ -> 0
#define isinf(x) (_fpclass(x)==_FPCLASS_PINF?1:(_fpclass(x)==_FPCLASS_NINF?-1:0))
#endif
}

/**
 * Decomposition utility class
 * A set of various static utility methods.
 */

class DecompositionUtils
{

public :

    /**
     * Tests whether a scalar value is a valid number,
     * that is, not a NaN.
     * @param[in] the scalar value to test.
     * @return 1 if the value is not a Nan, 0 if it is.
     */
    static int isANumber(double x);

    static int isANumber(int x)
    {
        return 1;
    }

    static int isANumber(unsigned int x)
    {
        return 1;
    }

    static int isANumber(char x)
    {
        return 1;
    }

    static int isANumber(unsigned char x)
    {
        return 1;
    }

    static int isANumber(short x)
    {
        return 1;
    }

    static int isANumber(unsigned short x)
    {
        return 1;
    }

    /**
     * Tests whether a scalar value is finite.
     * @param[in] the scalar value to test.
     * @return 1 if the value is finite, 0 if it is infinite.
     */
    static int isFinite(double x);

    /**
     * Tests whether a scalar value is valid.
     * The value is valid if it is neither infinite nor a NaN.
     * @param[in] the scalar value to test.
     * @return 1 if the value is valid, 0 if it is not.
     */
    static int isValid(double x);

    /**
     * Tests whether a point is valid.
     * The point is valid if none of its coordinates is infinite or a NaN.
     * @param[in] the point's x-coordinate.
     * @param[in] the point's y-coordinate.
     * @param[in] the point's z-coordinate.
     * @return 1 if the point is valid, 0 if it is not.
     */
    static int isValid(double x, double y, double z);

    /**
     * Tests whether a point is valid.
     * The point is valid if none of its coordinates is infinite or a NaN.
     * @param[in] the point's x-coordinate.
     * @param[in] the point's y-coordinate.
     * @return 1 if the point is valid, 0 if it is not.
     */
    static int isValid(double x, double y);

    /**
     * Returns the base-10 logarithm of the input value.
     * @param[in] the input value.
     * @return the base-10 logarithm of the input value.
     */
    static double getLog10Value(double value);

    /**
     * Determines if a single-component point is valid in logarithmic scale.
     * @param[in] the point's coordinate.
     * @return 1 if the point is valid, 0 if it is not.
     */
    static int isLogValid(double x);

    /**
     * Determines if a point is valid in logarithmic scale.
     * It checks whether any of its coordinates is strictly less than 0 (if the
     * logarithmic scale applies). In the event of the former, the point is
     * determined as not valid.
     * @param[in] the point's x-coordinate.
     * @param[in] the point's y-coordinate.
     * @param[in] the bit mask specifying for which coordinates the logarithmic scale is used.
     * @return 1 if the point is valid, 0 if it is not.
     */
    static int isLogValid(double x, double y, int logMask);

    /**
     * Determines if a point is valid in logarithmic scale.
     * It checks whether any of its coordinates is strictly less than 0 (if the
     * logarithmic scale applies). In the event of the former, the point is
     * determined as not valid.
     * @param[in] the point's x-coordinate.
     * @param[in] the point's y-coordinate.
     * @param[in] the point's z-coordinate.
     * @param[in] the bit mask specifying for which coordinates the logarithmic scale is used.
     * @return 1 if the point is valid, 0 if it is not.
     */
    static int isLogValid(double x, double y, double z, int logMask);

    /**
     * Returns the maximum representable double value.
     * @return the maximum representable double value.
     */
    static double getMaxDoubleValue(void);

    /**
     * Returns the minimum representable double value.
     * @return the minimum representable double value.
     */
    static double getMinDoubleValue(void);

    /**
     * Returns the absolute value of its input value.
     * @param[in] the value.
     * @return the absolute value.
     */
    static double getAbsoluteValue(double value);

    /**
     * Returns the square root of its input value.
     * @param[in] the value.
     * @return the value's square root.
     */
    static double getSquareRoot(double value);

    /**
     * Utility function which outputs the triangle indices of a rectangle decomposed
     * into 2 adjacent triangles. Decomposition is always performed the same way as it does not
     * depend on input vertex values. This function should therefore be used only for rectangles.
     * @param[out] the triangle indices (v0, v1, v2), (v3, v4, v5).
     */
    static void getDecomposedRectangleTriangleIndices(int* indices);

    /**
     * Decomposes a quadrilateral facet into two triangles and outputs the resulting vertex indices.
     * As there are two possible decompositions, it chooses the one which has the most coplanar triangles.
     * The output triangles' vertex indices are in counter-clockwise order.
     * @param[in] the facet vertices (4 (x,y,z) triplets, in counter-clockwise order).
     * @param[in] the facet vertices' indices (4 elements, in counter-clockwise order).
     * @param[out] the triangles' vertex indices (6 elements: two consecutive index triplets).
     */
    static void getDecomposedQuadTriangleIndices(double vertices[4][3], int* facetVertexIndices, int* triangleVertexIndices);
};

inline int DecompositionUtils::isANumber(double x)
{
    return isnan(x) ? 0 : 1;
}

inline int DecompositionUtils::isFinite(double x)
{
    return isinf(x) ? 0 : 1;
}

inline int DecompositionUtils::isValid(double x)
{
    return isnan(x) || isinf(x) ? 0 : 1;
}

inline int DecompositionUtils::isValid(double x, double y, double z)
{
    return isnan(x) || isnan(y) || isnan(z) || isinf(x) || isinf(y) || isinf(z) ? 0 : 1;
}

inline int DecompositionUtils::isValid(double x, double y)
{
    return isnan(x) || isnan(y) || isinf(x) || isinf(y) ? 0 : 1;
}

inline double DecompositionUtils::getLog10Value(double value)
{
    return log10(value);
}

inline int DecompositionUtils::isLogValid(double x)
{
    return x > 0.0 ? 1 : 0;
}

inline int DecompositionUtils::isLogValid(double x, double y, double z, int logMask)
{
    int valid = 1;

    if (logMask & 0x1)
    {
        valid &= (x > 0.0);
    }

    if (logMask & 0x2)
    {
        valid &= (y > 0.0);
    }

    if (logMask & 0x4)
    {
        valid &= (z > 0.0);
    }

    return valid;
}

inline int DecompositionUtils::isLogValid(double x, double y, int logMask)
{
    int valid = 1;

    if (logMask & 0x1)
    {
        valid &= (x > 0.0);
    }

    if (logMask & 0x2)
    {
        valid &= (y > 0.0);
    }

    return valid;
}

inline double DecompositionUtils::getMaxDoubleValue(void)
{
    return DBL_MAX;
}

inline double DecompositionUtils::getMinDoubleValue(void)
{
    return DBL_MIN;
}

inline double DecompositionUtils::getAbsoluteValue(double value)
{
    return fabs(value);
}

inline double DecompositionUtils::getSquareRoot(double value)
{
    return sqrt(value);
}

/*
 * Decomposes a rectangle into two adjacent triangles.
 * The rectangle's vertices are supposed to be specified in
 * counter-clockwise order, with 0 corresponding to the former's lower-left vertex.
 * The two output triangles' vertex indices are also specified in
 * counter-clockwise order.
 */
inline void DecompositionUtils::getDecomposedRectangleTriangleIndices(int* indices)
{
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
}

#endif
