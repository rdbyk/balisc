/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2013 - Scilab Enterprises - Paul Bignier
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

#include <stdio.h>
#include "doublecomplex.h"
#include "api_scilab.h"
#include "gw_linear_algebra2.h"
#include "Scierror.h"
#include "localization.h"
#include "sci_malloc.h"
#include "norm.h"
#include "strcmp.h"

int sci_norm(char *fname, void* pvApiCtx)
{
    SciErr sciErr;
    // Arguments' addresses
    int *pAAddr         = NULL;
    int *pflagAddr      = NULL;
    // Arguments' values
    double *pA          = NULL;
    char *pflagChar     = NULL;
    doublecomplex *pAC  = NULL;
    double flagVal = 0;
    // Arguments' properties (type, dimensions, length)
    int iLen = 0;
    int iType = 0;
    int iRows = 0;
    int iCols = 0;
    // Return value
    double ret = 0;

    int isMat = 0;
    int isComplex = 0;

    CheckInputArgument(pvApiCtx, 1, 2);
    CheckOutputArgument(pvApiCtx, 0, 1);

    // Checking A.
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &pAAddr); // Retrieving A address.
    if (sciErr.iErr)
    {
        Scierror(999, _("%s: Can not read input argument #%d.\n"), fname, 1);
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarType(pvApiCtx, pAAddr, &iType); // Retrieving A type.
    if (iType != sci_matrix)
    {
        OverLoad(1);
        return 0;
    }

    if (isVarComplex(pvApiCtx, pAAddr))
    {
        sciErr = getComplexZMatrixOfDouble(pvApiCtx, pAAddr, &iRows, &iCols, &pAC);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            Scierror(202, _("%s: Wrong type for argument #%d: Real or complex matrix expected.\n"), fname, 1);
            return 0;
        }

        isComplex = 1;

        int i;
        for (i = 0; i < iRows * iCols; ++i) // Checking A for %inf, which is not supported by Lapack.
        {
            if (la_isinf(pAC[i].r) != 0 || la_isinf(pAC[i].i) != 0 || ISNAN(pAC[i].r) || ISNAN(pAC[i].i))
            {
                Scierror(264, _("%s: Wrong value for argument #%d: Must not contain NaN or Inf.\n"), fname, 1);
                return 0;
            }
        }
    }
    else
    {
        sciErr = getMatrixOfDouble(pvApiCtx, pAAddr, &iRows, &iCols, &pA);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            Scierror(202, _("%s: Wrong type for argument #%d: Real or complex matrix expected.\n"), fname, 1);
            return 0;
        }

        int i;
        for (i = 0 ; i < iRows * iCols ; i++) // Checking A for %inf, which is not supported by Lapack.
        {
            if (la_isinf(pA[i]) != 0 || ISNAN(pA[i]))
            {
                Scierror(264, _("%s: Wrong value for argument #%d: Must not contain NaN or Inf.\n"), fname, 1);
                return 0;
            }
        }
    }

    switch (iRows)
    {
        case -1: // FIXME: better check for eye() ?
            // pretend that eye() is 1x1-matrix, in order to make
            // the underlying LAPACK stuff happy
            iRows = 1;
            iCols = 1;
            break;

        case 0: // norm([]) => result is 0.0
            createScalarDouble(pvApiCtx, Rhs + 1, 0.0);
            AssignOutputVariable(pvApiCtx, 1) = Rhs + 1;
            return 0;

        case 1: // transpose row vector => col vector
            {
                int iTemp = iRows;
                iRows = iCols;
                iCols = iTemp;
            }
            break;

        default: // iRows > 1
            if (iCols > 1)
            {
                // matrix case
                isMat = 1;
            }
            break;
    }

    if (Rhs == 1) // One argument => returning norm 2.
    {
        // Call normP() or normPC().
        if (isComplex)
        {
            ret = normPC(pAC, iRows, iCols, 2); // if A is a complex matrix, call the complex function.
        }
        else
        {
            ret = normP(pA, iRows, iCols, 2);
        }

        createScalarDouble(pvApiCtx, Rhs + 1, ret);
        AssignOutputVariable(pvApiCtx, 1) = Rhs + 1;
        return 0;
    }

    // Checking flag.
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &pflagAddr); // Retrieving flag address.
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarType(pvApiCtx, pflagAddr, &iType); // Retrieving flag type.
    if (iType != sci_strings && iType != sci_matrix)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: String or integer expected.\n"), fname, 2);
        return 0;
    }

    if (iType == sci_strings)
    {
        if (getAllocatedSingleString(pvApiCtx, pflagAddr, &pflagChar)) // Retrieving flag dimensions.
        {
            Scierror(205, _("%s: Wrong size for input argument #%d: string expected.\n"), fname, 2);
            return 0;
        }

        iLen = (int)strlen(pflagChar);
        if (iLen != 3 && iLen != 1)
        {
            Scierror(116, _("%s: Wrong value for input argument #%d: %s, %s, %s, or %s expected.\n"), fname, 2, "i", "inf", "f", "fro");
            freeAllocatedSingleString(pflagChar);
            return 0;
        }

        if (balisc_strcmp(pflagChar, "inf") != 0 && balisc_strcmp(pflagChar, "i") != 0 &&
                balisc_strcmp(pflagChar, "fro") != 0 && balisc_strcmp(pflagChar, "f") != 0) // flag must be = "inf", "i", "fro" or "f".
        {
            Scierror(116, _("%s: Wrong value for input argument #%d: %s, %s, %s or %s expected.\n"), fname, 2, "i", "inf", "f", "fro");
            freeAllocatedSingleString(pflagChar);
            return 0;
        }

        if (isComplex)
        {
            ret = normStringC(pAC, iRows, iCols, pflagChar); // if A is a complex matrix, call the complex function.
        }
        else
        {
            ret = normString(pA, iRows, iCols, pflagChar); // flag is a string => returning the corresponding norm.
        }

        createScalarDouble(pvApiCtx, Rhs + 1, ret);
        AssignOutputVariable(pvApiCtx, 1) = Rhs + 1;
        freeAllocatedSingleString(pflagChar);
        return 0;
    }
    else
    {
        if (isVarComplex(pvApiCtx, pflagAddr))
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: A real expected.\n"), fname, 2);
            return 0;
        }
        if (getScalarDouble(pvApiCtx, pflagAddr, &flagVal)) // Retrieving flag value & dimensions as a double.
        {
            printError(&sciErr, 0);
            Scierror(999, _("%s: Wrong size for input argument #%d: A real scalar expected.\n"), fname, 2);
            return 0;
        }

        // Call the norm functions.
        if (la_isinf(flagVal) == 1 && flagVal > 0) // flag = %inf
        {
            if (isComplex)
            {
                ret = normStringC(pAC, iRows, iCols, "inf"); // if A is a complex matrix, call the complex function.
            }
            else
            {
                ret = normString(pA, iRows, iCols, "inf"); // The infinite norm is computed by normString().
            }

            createScalarDouble(pvApiCtx, Rhs + 1, ret);
            AssignOutputVariable(pvApiCtx, 1) = Rhs + 1;
            return 0;
        }
        else
        {
            if (isMat == 1 && flagVal != 1 && flagVal != 2 && la_isinf(flagVal) == 0)
            {
                Scierror(116, _("%s: Wrong value for input argument #%d: %s, %s, %s or %s expected.\n"), fname, 2, "1", "2", "inf", "-inf");
                return 0;
            }

            if (isComplex)
            {
                ret = normPC(pAC, iRows, iCols, flagVal); // if A is a complex matrix, call the complex function.
            }
            else
            {
                ret = normP(pA, iRows, iCols, flagVal); // flag is an integer => returning the corresponding norm.
            }

            createScalarDouble(pvApiCtx, Rhs + 1, ret);
            AssignOutputVariable(pvApiCtx, 1) = Rhs + 1;
            return 0;
        }
    }

    return 0;
}
