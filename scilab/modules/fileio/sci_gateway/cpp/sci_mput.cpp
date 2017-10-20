/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Allan CORNET
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
 *
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

/*--------------------------------------------------------------------------*/
#include "filemanager.hxx"
#include "fileio_gw.hxx"
#include "string.hxx"
#include "double.hxx"
#include "int.hxx"
#include "function.hxx"
#include "mputi.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "mput.h"
#include "localization.h"
#include "Scierror.h"
#include "charEncoding.h"
#include "os_string.h"
}

/*--------------------------------------------------------------------------*/
types::Function::ReturnValue sci_mput(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    char* pstType = os_strdup("l");//default type value : long
    int iSize = 0;
    int iFile = -1; //default file : last opened file
    double* pData = NULL;
    int iErr = 0;

    if (in.size() < 1 || in.size() > 3)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d to %d expected.\n"), "mput", 1, 3);
        FREE(pstType);
        return types::Function::Error;
    }

    //check parameter 1
    if ((in[0]->isDouble() == false) && (in[0]->isInt() == false))
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A integer expected.\n"), "mput", 1);
        FREE(pstType);
        return types::Function::Error;
    }

    iSize = in[0]->getAs<types::GenericType>()->getSize();

    if (in.size() >= 2)
    {
        //export format
        if (in[1]->isString() == false || in[1]->getAs<types::String>()->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), "mput", 2);
            FREE(pstType);
            return types::Function::Error;
        }

        FREE(pstType);
        pstType = wide_string_to_UTF8(in[1]->getAs<types::String>()->getFirst());

    }

    if (in.size() == 3)
    {
        if (in[2]->isDouble() == false || in[2]->getAs<types::Double>()->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: A integer expected.\n"), "mput", 3);
            FREE(pstType);
            return types::Function::Error;
        }

        iFile = static_cast<int>(in[2]->getAs<types::Double>()->getFirst());
    }

    switch (iFile)
    {
        case 5: // stdin
            Scierror(999, _("%s: Wrong file descriptor: %d.\n"), "mput", iFile);
            FREE(pstType);
            return types::Function::Error;
    }

    if (in[0]->isDouble())
    {
        int iErr = 0;
        pData = in[0]->getAs<types::Double>()->get();
        C2F(mput)(&iFile, pData, &iSize, pstType, &iErr);

        if (iErr)
        {
            FREE(pstType);
            Scierror(10000, "");
            return types::Function::Error;
        }
    }
    else
    {
        int err = 0;
        switch (in[0]->getType())
        {
            case types::InternalType::ScilabInt8:
            {
                char* piData = NULL;
                piData = in[0]->getAs<types::Int8>()->get();
                err = mputi(iFile, piData, iSize, pstType);
                break;
            }
            case types::InternalType::ScilabInt16:
            {
                short* piData = NULL;
                piData = in[0]->getAs<types::Int16>()->get();
                err = mputi(iFile, piData, iSize, pstType);
                break;
            }
            case types::InternalType::ScilabInt32:
            {
                int* piData = NULL;
                piData = in[0]->getAs<types::Int32>()->get();
                err = mputi(iFile, piData, iSize, pstType);
                break;
            }
            case types::InternalType::ScilabInt64:
            {
                long long* piData = NULL;
                piData = in[0]->getAs<types::Int64>()->get();
                err = mputi(iFile, piData, iSize, pstType);
                break;
            }
            case types::InternalType::ScilabUInt8:
            {
                unsigned char* piData = NULL;
                piData = in[0]->getAs<types::UInt8>()->get();
                err = mputi(iFile, piData, iSize, pstType);
                break;
            }
            case types::InternalType::ScilabUInt16:
            {
                unsigned short* piData = NULL;
                piData = in[0]->getAs<types::UInt16>()->get();
                err = mputi(iFile, piData, iSize, pstType);
                break;
            }
            case types::InternalType::ScilabUInt32:
            {
                unsigned int* piData = NULL;
                piData = in[0]->getAs<types::UInt32>()->get();
                err = mputi(iFile, piData, iSize, pstType);
                break;
            }
            case types::InternalType::ScilabUInt64:
            {
                unsigned long long* piData = NULL;
                piData = in[0]->getAs<types::UInt64>()->get();
                err = mputi(iFile, piData, iSize, pstType);
                break;
            }
        }

        if (err)
        {
            FREE(pstType);
            Scierror(10000, "");
            return types::Function::Error;
        }
    }

    FREE(pstType);
    return types::Function::OK;
}
/*--------------------------------------------------------------------------*/
