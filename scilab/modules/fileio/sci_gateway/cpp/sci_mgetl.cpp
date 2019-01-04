/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Allan CORNET
 * Copyright (C) 2010 - DIGITEO - Allan CORNET
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

#include "filemanager.hxx"
#include "fileio_gw.hxx"
#include "string.hxx"
#include "double.hxx"
#include "function.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "mgetl.h"
#include "localization.h"
#include "Scierror.h"
#include "mopen.h"
#include "mclose.h"
#include "expandPathVariable.h"
#include "freeArrayOfPtrs.h"
}

static const char fname[] = "mgetl";

types::Function::ReturnValue sci_mgetl(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int iFileID = 0;
    bool bCloseFile = false;
    int iLinesExpected = -1;
    int iLinesRead = -1;
    wchar_t** wcReadStrings = NULL;

    if (in.size() < 1 || in.size() > 2)
    {
        Scierror(72, 1, 2);
        return types::Function::OK;
    }

    if (in.size() == 2)
    {
        //number of lines
        if (in[1]->isDouble() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: An integer value expected.\n"), fname, 2);
            return types::Function::Error;
        }

        if (in[1]->getAs<types::Double>()->isScalar() == false)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: An integer value expected.\n"), fname, 2);
            return types::Function::Error;
        }

        if (in[1]->getAs<types::Double>()->getFirst() != (int)in[1]->getAs<types::Double>()->getFirst())
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: An integer value expected.\n"), fname, 2);
            return types::Function::Error;
        }

        iLinesExpected = static_cast<int>(in[1]->getAs<types::Double>()->getFirst());
    }

    if (in[0]->isDouble() && in[0]->getAs<types::Double>()->getSize() == 1)
    {
        iFileID = static_cast<int>(in[0]->getAs<types::Double>()->getFirst());
    }
    else if (in[0]->isString() && in[0]->getAs<types::String>()->getSize() == 1)
    {
        wchar_t *expandedFileName = expandPathVariableW(in[0]->getAs<types::String>()->getFirst());

        int iErr = mopen(expandedFileName, L"rt", 0, &iFileID);

        if (iErr)
        {
            char* pst = wide_string_to_UTF8(expandedFileName);
            switch (iErr)
            {
                case MOPEN_NO_MORE_LOGICAL_UNIT:
                    Scierror(66, _("%s: Too many files opened!\n"), fname);
                    break;
                case MOPEN_CAN_NOT_OPEN_FILE:
                    Scierror(999, _("%s: Cannot open file %s.\n"), fname, pst);
                    break;
                case MOPEN_NO_MORE_MEMORY:
                    Scierror(999, _("%s: No more memory.\n"), fname);
                    break;
                case MOPEN_INVALID_FILENAME:
                    Scierror(999, _("%s: invalid filename %s.\n"), fname, pst);
                    break;
                default: //MOPEN_INVALID_STATUS
                    Scierror(999, _("%s: invalid status.\n"), fname);
                    break;
            }

            FREE(pst);
            FREE(expandedFileName);
            return types::Function::Error;
        }
        FREE(expandedFileName);
        bCloseFile = true;
    }
    else
    {
        //Error
        Scierror(999, _("%s: Wrong type for input argument #%d: a String or Integer expected.\n"), fname, 1);
        return types::Function::Error;
    }

    switch (iFileID)
    {
        case 0: // stderr
        case 6: // stdout
            Scierror(30, iFileID);
            return types::Function::Error;
        default :
        {
            types::File* pFile = FileManager::getFile(iFileID);
            // file opened with fortran open function
            if (pFile == NULL || pFile->getFileType() == 1)
            {
                Scierror(30, iFileID);
                return types::Function::Error;
            }

            if ((iLinesExpected > 0) && (iFileID == 5))
            {
                iLinesExpected = 1;
            }

            iLinesRead = mgetl(iFileID, iLinesExpected, &wcReadStrings);
        }
    }

    if (wcReadStrings && iLinesRead > 0)
    {
        types::String *pS = new types::String(iLinesRead, 1);
        pS->set(wcReadStrings);
        out.push_back(pS);
        freeArrayOfPtrs((void**)wcReadStrings, iLinesRead);
    }
    else
    {
        out.push_back(types::Double::Empty());
        if (wcReadStrings)
        {
            FREE(wcReadStrings);
        }
    }

    if (bCloseFile)
    {
        mclose(iFileID);
    }

    return types::Function::OK;
}
