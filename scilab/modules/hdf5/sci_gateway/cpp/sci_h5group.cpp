/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Calixte DENIZET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include <string>

extern "C"
{
#include "gw_hdf5.h"
#include "Scierror.h"
#include "api_scilab.h"
#include "localization.h"
#include "expandPathVariable.h"
}

#include "H5Group.hxx"
#include "HDF5Scilab.hxx"

using namespace org_modules_hdf5;

/*
  Create a group
  Scilab prototype:
  - h5group(obj, name)
  - h5group(filename, name)
*/

int sci_h5group(char *fname, int* pvApiCtx)
{
    H5Object * hobj = 0;
    SciErr err;
    int * addr = 0;
    char * str = 0;
    char ** strs = 0;
    char * expandedPath = 0;
    std::string _expandedPath;
    const int nbIn = nbInputArgument(pvApiCtx);
    int row, col;

    CheckOutputArgument(pvApiCtx, 0, 1);
    CheckInputArgument(pvApiCtx, 2, 2);

    err = getVarAddressFromPosition(pvApiCtx, 1, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 1);
        return 0;
    }

    if (HDF5Scilab::isH5Object(addr, pvApiCtx))
    {
        hobj = HDF5Scilab::getH5Object(addr, pvApiCtx);
        if (!hobj)
        {
            Scierror(130);
            return 0;
        }
    }
    else
    {
        err = getVarAddressFromPosition(pvApiCtx, 1, &addr);
        if (err.iErr)
        {
            printError(&err, 0);
            Scierror(47, 1);
            return 0;
        }

        if (!isStringType(pvApiCtx, addr) || !checkVarDimension(pvApiCtx, addr, 1, 1))
        {
            Scierror(91, 1);
            return 0;
        }

        if (getAllocatedSingleString(pvApiCtx, addr, &str) != 0)
        {
            Scierror(1);
            return 0;
        }

        expandedPath = expandPathVariable(str);
        _expandedPath = std::string(expandedPath);
        FREE(expandedPath);
        freeAllocatedSingleString(str);
    }

    err = getVarAddressFromPosition(pvApiCtx, 2, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 2);
        return 0;
    }

    if (!isStringType(pvApiCtx, addr))
    {
        Scierror(91, 2);
        return 0;
    }

    if (getAllocatedMatrixOfString(pvApiCtx, addr, &row, &col, &strs) != 0)
    {
        Scierror(1);
        return 0;
    }

    try
    {
        if (hobj)
        {
            HDF5Scilab::createGroup(*hobj, row * col, const_cast<const char **>(strs));
        }
        else
        {
            HDF5Scilab::createGroup(_expandedPath, row * col, const_cast<const char **>(strs));
        }
        freeAllocatedMatrixOfString(row, col, strs);
    }
    catch (const std::exception & e)
    {
        freeAllocatedMatrixOfString(row, col, strs);
        Scierror(132, e.what());
        return 0;
    }

    AssignOutputVariable(pvApiCtx, 1) = 0;
    ReturnArguments(pvApiCtx);

    return 0;
}
