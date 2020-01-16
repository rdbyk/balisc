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
}

#include "HDF5Scilab.hxx"

using namespace org_modules_hdf5;

/*
  List the content of an object.
  Scilab prototype:
  - h5get(obj, name)
  - h5get(obj, name, isAttr)
*/

/*--------------------------------------------------------------------------*/
int sci_h5get(char * fname, int* pvApiCtx)
{
    H5Object * hobj = 0;
    SciErr err;
    int * addr = 0;
    char * str = 0;
    std::string name;
    bool isAttr = false;;
    int _isAttr;
    const int nbIn = nbInputArgument(pvApiCtx);

    CheckOutputArgument(pvApiCtx, 0, 1);
    CheckInputArgument(pvApiCtx, 2, 3);

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
        Scierror(90, 1, _("H5Object"));
        return 0;
    }

    err = getVarAddressFromPosition(pvApiCtx, 2, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 2);
        return 0;
    }

    if (!isStringType(pvApiCtx, addr) || !checkVarDimension(pvApiCtx, addr, 1, 1))
    {
        Scierror(91, 2);
        return 0;
    }

    if (getAllocatedSingleString(pvApiCtx, addr, &str) != 0)
    {
        Scierror(1);
        return 0;
    }

    name = std::string(str);
    freeAllocatedSingleString(str);

    if (nbIn == 3)
    {
        err = getVarAddressFromPosition(pvApiCtx, 3, &addr);
        if (err.iErr)
        {
            printError(&err, 0);
            Scierror(47, 3);
            return 0;
        }

        if (!isBooleanType(pvApiCtx, addr) || !checkVarDimension(pvApiCtx, addr, 1, 1))
        {
            Scierror(999, _("%s: Wrong size for input argument #%d.\n"), fname, 3);
            return 0;
        }

        if (getScalarBoolean(pvApiCtx, addr, &_isAttr) != 0)
        {
            Scierror(1);
            return 0;
        }

        isAttr = _isAttr != 0;
    }

    try
    {
        HDF5Scilab::getObject(*hobj, name, isAttr, nbIn + 1, pvApiCtx);
    }
    catch (const std::exception & e)
    {
        Scierror(132, e.what());
        return 0;
    }

    AssignOutputVariable(pvApiCtx, 1) = nbIn + 1;
    ReturnArguments(pvApiCtx);

    return 0;
}
