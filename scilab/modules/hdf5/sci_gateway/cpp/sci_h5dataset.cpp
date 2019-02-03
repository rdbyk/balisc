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
}

#include "HDF5Scilab.hxx"

using namespace org_modules_hdf5;

/*
  Create a new dataset (equivalent to h5write).
  Scilab prototype:
*/

int sci_h5dataset(char *fname, int* pvApiCtx)
{
    H5Object * hobj = 0;
    SciErr err;
    int * addr = 0;
    char * str = 0;
    std::string name;
    std::string targetType;
    std::string sourceType;
    std::string file;
    hsize_t * sdims = 0;
    hsize_t * sstart = 0;
    hsize_t * sstride = 0;
    hsize_t * scount = 0;
    hsize_t * sblock = 0;
    hsize_t ** sourcePtrs[5] = {&sdims, &sstart, &scount, &sstride, &sblock};
    hsize_t * ddims = 0;
    hsize_t * dstart = 0;
    hsize_t * dstride = 0;
    hsize_t * dcount = 0;
    hsize_t * dblock = 0;
    hsize_t * dextent = 0;
    hsize_t ** destPtrs[6] = {&ddims, &dextent, &dstart, &dcount, &dstride, &dblock};
    double * sdptr = 0;
    double * ddptr = 0;
    int row, col;
    bool hasSourceType = false;
    unsigned int size = 0;
    const int nbIn = nbInputArgument(pvApiCtx);

    CheckOutputArgument(pvApiCtx, 1, 1);
    CheckInputArgument(pvApiCtx, 5, 7);

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
        if (!isStringType(pvApiCtx, addr) || !checkVarDimension(pvApiCtx, addr, 1, 1))
        {
            Scierror(90, 1,  _("string or H5Object"));
            return 0;
        }

        if (getAllocatedSingleString(pvApiCtx, addr, &str) != 0)
        {
            Scierror(1);
            return 0;
        }

        file = std::string(str);
        freeAllocatedSingleString(str);
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

    err = getVarAddressFromPosition(pvApiCtx, 3, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 3);
        return 0;
    }

    if (!isDoubleType(pvApiCtx, addr))
    {
        Scierror(94, 3);
        return 0;
    }

    err = getMatrixOfDouble(pvApiCtx, addr, &row, &col, &sdptr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 3);
        return 0;
    }

    if (row != 5)
    {
        Scierror(100, 3, _("(5,n)-vector"));
        return 0;
    }

    size = (unsigned int)col;

    err = getVarAddressFromPosition(pvApiCtx, 5, &addr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, 5);
        return 0;
    }

    if (isStringType(pvApiCtx, addr))
    {
        if (!checkVarDimension(pvApiCtx, addr, 1, 1))
        {
            Scierror(91, 5);
            return 0;
        }

        if (getAllocatedSingleString(pvApiCtx, addr, &str) != 0)
        {
            Scierror(1);
            return 0;
        }

        sourceType = std::string(str);
        freeAllocatedSingleString(str);
        hasSourceType = true;
    }

    if (hasSourceType)
    {
        err = getVarAddressFromPosition(pvApiCtx, 6, &addr);
        if (err.iErr)
        {
            printError(&err, 0);
            Scierror(47, 6);
            return 0;
        }
    }

    if (!isDoubleType(pvApiCtx, addr))
    {
        Scierror(94, hasSourceType ? 6 : 5);
        return 0;
    }

    err = getMatrixOfDouble(pvApiCtx, addr, &row, &col, &ddptr);
    if (err.iErr)
    {
        printError(&err, 0);
        Scierror(47, hasSourceType ? 6 : 5);
        return 0;
    }

    if (row != 6)
    {
        Scierror(100, hasSourceType ? 6 : 5, _("(6,n)-vector"));
        return 0;
    }

    if (col != size)
    {
        Scierror(999, _("%s: Wrong size for input argument #%d: %d column vector expected.\n"), fname, hasSourceType ? 6 : 5, size);
        return 0;
    }

    if ((hasSourceType && nbIn == 7) || (!hasSourceType && nbIn == 6))
    {
        err = getVarAddressFromPosition(pvApiCtx, nbIn, &addr);
        if (err.iErr)
        {
            printError(&err, 0);
            Scierror(47, nbIn);
            return 0;
        }

        if (!isStringType(pvApiCtx, addr) || !checkVarDimension(pvApiCtx, addr, 1, 1))
        {
            Scierror(91, 5);
            return 0;
        }

        if (getAllocatedSingleString(pvApiCtx, addr, &str) != 0)
        {
            Scierror(1);
            return 0;
        }

        targetType = std::string(str);
        freeAllocatedSingleString(str);
    }

    for (unsigned int i = 0; i < 5; i++)
    {
        *sourcePtrs[i] = new hsize_t[size];
        for (unsigned int j = 0; j < size; j++)
        {
            (*sourcePtrs[i])[j] = (hsize_t)(sdptr[i + j * 5]);
        }
    }

    for (unsigned int i = 0; i < 6; i++)
    {
        *destPtrs[i] = new hsize_t[size];
        for (unsigned int j = 0; j < size; j++)
        {
            (*destPtrs[i])[j] = (hsize_t)(ddptr[i + j * 6]);
        }
    }

    try
    {
        if (hobj)
        {
            HDF5Scilab::createObjectFromStack<H5Dataset>(*hobj, "", name, false, pvApiCtx, 4, size, sdims, sstart, sstride, scount, sblock, targetType, size, ddims, dextent, dstart, dstride, dcount, dblock);
        }
        else
        {
            HDF5Scilab::createObjectFromStack<H5Dataset>(file, "/", name, false, pvApiCtx, 4, size, sdims, sstart, sstride, scount, sblock, targetType, size, ddims, dextent, dstart, dstride, dcount, dblock);
        }

        for (unsigned int i = 0; i < 5; i++)
        {
            delete[] *sourcePtrs[i];
        }
        for (unsigned int i = 0; i < 6; i++)
        {
            delete[] *destPtrs[i];
        }
    }
    catch (const H5Exception & e)
    {
        for (unsigned int i = 0; i < 5; i++)
        {
            delete[] *sourcePtrs[i];
        }
        for (unsigned int i = 0; i < 6; i++)
        {
            delete[] *destPtrs[i];
        }
        Scierror(132, e.what());
        return 0;
    }

    AssignOutputVariable(pvApiCtx, 1) = 0;
    ReturnArguments(pvApiCtx);

    return 0;
}
