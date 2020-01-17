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

extern "C"
{
#include "gw_hdf5.h"
#include "Scierror.h"
#include "api_scilab.h"
#include "localization.h"
#include "expandPathVariable.h"
}

#include "HDF5Scilab.hxx"
#include "H5File.hxx"

using namespace org_modules_hdf5;

/*
  Copy an object (this code has been copied for h5mv).
  Scilab prototype:
  - h5cp(srcobj, destobj)
  - h5cp(srcobj, destobj, destloc)
  - h5cp(srcobj, destfile, destloc)
  - h5cp(srcobj, sloc, destobj)
  - h5cp(srcobj, sloc, destobj, destloc)
  - h5cp(srcobj, sloc, destfile, destloc)
  - h5cp(srcfile, sloc, destobj)
  - h5cp(srcfile, sloc, destobj, destloc)
  - h5cp(srcfile, sloc, destfile, destloc)
*/

/*--------------------------------------------------------------------------*/
int sci_h5cp(char *fname, int* pvApiCtx)
{
    SciErr err;
    H5Object * sobj = 0;
    H5Object * dobj = 0;
    int * addr = 0;
    char * str = 0;
    char * expandedPath = 0;
    std::string sfile;
    std::string dfile;
    std::string sloc;
    std::string dloc;
    const int nbIn = nbInputArgument(pvApiCtx);

    CheckOutputArgument(pvApiCtx, 0, 1);
    CheckInputArgument(pvApiCtx, 2, 4);

    err = getVarAddressFromPosition(pvApiCtx, 1, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 1);
        return 0;
    }

    if (HDF5Scilab::isH5Object(addr, pvApiCtx))
    {
        sobj = HDF5Scilab::getH5Object(addr, pvApiCtx);
        if (!sobj)
        {
            Scierror(130);
            return 0;
        }
    }
    else
    {
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
        freeAllocatedSingleString(str);
        sfile = std::string(expandedPath);
        FREE(expandedPath);
    }

    err = getVarAddressFromPosition(pvApiCtx, 2, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 2);
        return 0;
    }

    if (HDF5Scilab::isH5Object(addr, pvApiCtx))
    {
        dobj = HDF5Scilab::getH5Object(addr, pvApiCtx);
        if (!dobj)
        {
            Scierror(130);
            return 0;
        }
    }
    else
    {
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

        sloc = std::string(str);
        freeAllocatedSingleString(str);
    }

    if (nbIn >= 3)
    {
        err = getVarAddressFromPosition(pvApiCtx, 3, &addr);
        if (err.iErr)
        {
            printError(&err, 0);
            Scierror(47, 3);
            return 0;
        }

        if (HDF5Scilab::isH5Object(addr, pvApiCtx))
        {
            dobj = HDF5Scilab::getH5Object(addr, pvApiCtx);
            if (!dobj)
            {
                Scierror(130);
                return 0;
            }
        }
        else
        {
            if (!isStringType(pvApiCtx, addr) || !checkVarDimension(pvApiCtx, addr, 1, 1))
            {
                Scierror(91, 3);
                return 0;
            }

            if (getAllocatedSingleString(pvApiCtx, addr, &str) != 0)
            {
                Scierror(1);
                return 0;
            }

            if (nbIn == 4)
            {
                expandedPath = expandPathVariable(str);
                dfile = std::string(expandedPath);
                FREE(expandedPath);
            }
            else
            {
                if (sobj)
                {
                    expandedPath = expandPathVariable(const_cast<char *>(sloc.c_str()));
                    dfile = std::string(expandedPath);
                    FREE(expandedPath);
                    dfile = sloc;
                    sloc = std::string("");
                }
                dloc = std::string(str);
            }
            freeAllocatedSingleString(str);
        }

        if (nbIn == 4)
        {
            err = getVarAddressFromPosition(pvApiCtx, 4, &addr);
            if (err.iErr)
            {
                printError(&err, 0);
                Scierror(47, 4);
                return 0;
            }

            if (!isStringType(pvApiCtx, addr) || !checkVarDimension(pvApiCtx, addr, 1, 1))
            {
                Scierror(91, 3);
                return 0;
            }

            if (getAllocatedSingleString(pvApiCtx, addr, &str) != 0)
            {
                Scierror(1);
                return 0;
            }

            dloc = std::string(str);
            freeAllocatedSingleString(str);
        }
    }

    try
    {
        if (sobj)
        {
            if (dobj)
            {
                HDF5Scilab::copy(*sobj, sloc, *dobj, dloc);
            }
            else
            {
                HDF5Scilab::copy(*sobj, sloc, dfile, dloc);
            }
        }
        else
        {
            if (dobj)
            {
                HDF5Scilab::copy(sfile, sloc, *dobj, dloc);
            }
            else
            {
                HDF5Scilab::copy(sfile, sloc, dfile, dloc);
            }
        }
    }
    catch (const std::exception & e)
    {
        Scierror(132, e.what());
        return 0;
    }

    AssignOutputVariable(pvApiCtx, 1) = 0;
    ReturnArguments(pvApiCtx);

    return 0;
}
