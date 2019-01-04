/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Allan CORNET
 * ...
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "fileio_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "double.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "findfiles.h"
#include "localization.h"
#include "Scierror.h"
#include "expandPathVariable.h"
#include "PATH_MAX.h"
#include "os_string.h"
#include "scicurdir.h"
#include "freeArrayOfPtrs.h"
}

#ifdef _MSC_VER
#define DEFAULT_FILESPEC L"*.*"
#else
#define DEFAULT_FILESPEC L"*"
#endif

static const char fname[] = "findfiles";

types::Function::ReturnValue sci_findfiles(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    wchar_t* pwstPath   = NULL;
    wchar_t* pwstSpec   = NULL;
    bool bAllocatedSpec = false;

    if (in.size() > 2)
    {
        Scierror(72, 0, 2);
        return types::Function::Error;
    }

    if (in.size() == 0)
    {
        //default path and default file spec
        int ierr        = 0;

        pwstPath        = scigetcwdW(&ierr);
        pwstSpec        = os_wcsdup(DEFAULT_FILESPEC);
        bAllocatedSpec  = true;
    }
    else
    {
        //user path
        if (in[0]->isString() == false || in[0]->getAs<types::String>()->getSize() != 1)
        {
            Scierror(91, 1);
            return types::Function::Error;
        }

        pwstPath = expandPathVariableW(in[0]->getAs<types::String>()->get()[0]);

        if (in.size() == 2)
        {
            //user file spec
            if (in[1]->isString() == false || in[1]->getAs<types::String>()->getSize() != 1)
            {
                Scierror(91, 2);
                FREE(pwstPath);
                return types::Function::Error;
            }

            pwstSpec = in[1]->getAs<types::String>()->get()[0];
        }
        else
        {
            //default file spec
            pwstSpec        = os_wcsdup(DEFAULT_FILESPEC);
            bAllocatedSpec  = true;
        }
    }

    int iSize               = 0;
    wchar_t** pwstFilesList = NULL;

    pwstFilesList = findfilesW(pwstPath, pwstSpec, &iSize, FALSE);
    if (pwstFilesList)
    {
        types::String* pS = new types::String(iSize, 1);
        pS->set(pwstFilesList);
        freeArrayOfPtrs((void**)pwstFilesList, iSize);
        out.push_back(pS);
    }
    else
    {
        out.push_back(types::Double::Empty());
    }

    FREE(pwstPath);
    if (bAllocatedSpec)
    {
        FREE(pwstSpec);
    }

    return types::Function::OK;
}
