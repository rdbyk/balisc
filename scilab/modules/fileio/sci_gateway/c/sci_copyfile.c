/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009-2012 - DIGITEO - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */


#ifndef _MSC_VER
#include <errno.h>
#include <string.h>
#else
#include <windows.h>
#endif
#include "gw_fileio.h"
#include "sci_malloc.h"
#include "localization.h"
#include "api_scilab.h"
#include "Scierror.h"
#include "copyfile.h"
#include "FileExist.h"
#include "isdir.h"
#include "splitpath.h"
#include "freeArrayOfPtrs.h"
#include "charEncoding.h"
#include "expandPathVariable.h"
/*--------------------------------------------------------------------------*/
static wchar_t *getFilenameWithExtension(wchar_t* wcFullFilename);
static int returnCopyFileResultOnStack(int ierr, char *fname , void* pvApiCtx);
/*--------------------------------------------------------------------------*/
int sci_copyfile(char *fname, void* pvApiCtx)
{
    SciErr sciErr;
    int *piAddressVarOne = NULL;
    wchar_t *pStVarOne = NULL;
    wchar_t *pStVarOneExpanded = NULL;

    int *piAddressVarTwo = NULL;
    wchar_t *pStVarTwo = NULL;
    wchar_t *pStVarTwoExpanded = NULL;

    /* Check Input & Output parameters */
    CheckRhs(2, 2);
    CheckLhs(1, 2);

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressVarOne);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        Scierror(999, _("%s: Can not read input argument #%d.\n"), fname, 1);
        return 0;
    }

    if (isStringType(pvApiCtx, piAddressVarOne) == 0 || isScalar(pvApiCtx, piAddressVarOne) == 0)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), fname, 1);
        return 0;
    }

    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressVarTwo);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        Scierror(999, _("%s: Can not read input argument #%d.\n"), fname, 2);
        return 0;
    }

    if (isStringType(pvApiCtx, piAddressVarTwo) == 0 || isScalar(pvApiCtx, piAddressVarTwo) == 0)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), fname, 2);
        return 0;
    }

    if (getAllocatedSingleWideString(pvApiCtx, piAddressVarOne, &pStVarOne))
    {
        if (pStVarOne)
        {
            freeAllocatedSingleWideString(pStVarOne);
        }

        Scierror(1);
        return 0;
    }

    if (getAllocatedSingleWideString(pvApiCtx, piAddressVarTwo, &pStVarTwo))
    {
        if (pStVarTwo)
        {
            freeAllocatedSingleWideString(pStVarTwo);
        }

        freeAllocatedSingleWideString(pStVarOne);
        Scierror(1);
        return 0;
    }

    pStVarOneExpanded = expandPathVariableW(pStVarOne);
    pStVarTwoExpanded = expandPathVariableW(pStVarTwo);

    freeAllocatedSingleWideString(pStVarTwo);
    freeAllocatedSingleWideString(pStVarOne);

    if (pStVarOneExpanded == NULL)
    {
        if (pStVarTwoExpanded)
        {
            FREE(pStVarTwoExpanded);
        }

        Scierror(1);
        return 0;
    }

    if (pStVarTwoExpanded == NULL)
    {
        if (pStVarOneExpanded)
        {
            FREE(pStVarOneExpanded);
        }

        Scierror(1);
        return 0;
    }

    if (isdirW(pStVarOneExpanded) || FileExistW(pStVarOneExpanded))
    {
        int ierrCopy = 0;

        if (isdirW(pStVarOneExpanded) || FileExistW(pStVarOneExpanded))
        {
            if (isdirW(pStVarOneExpanded))
            {
                /* copy a directory into a directory */
                ierrCopy = CopyDirectoryFunction(pStVarTwoExpanded, pStVarOneExpanded);
            }
            else if (FileExistW(pStVarOneExpanded))
            {
                if (isdirW(pStVarTwoExpanded))
                {
                    /* copy file into a existing directory */
                    wchar_t *filename = getFilenameWithExtension(pStVarOneExpanded);

                    if (filename)
                    {
#define FORMAT_FULLFILENAME "%s/%s"
                        wchar_t *destFullFilename = NULL;
                        int len_StVarTwoExpanded = wcslen(pStVarTwoExpanded);
                        
                        /* remove last file separator if it exists */
                        if ((pStVarTwoExpanded[len_StVarTwoExpanded - 1] == L'\\') || (pStVarTwoExpanded[len_StVarTwoExpanded - 1] == L'/'))
                        {
                            pStVarTwoExpanded[len_StVarTwoExpanded - 1] = L'\0';
                        }

                        destFullFilename = (wchar_t *) MALLOC(sizeof(wchar_t) * (len_StVarTwoExpanded +
                                                              (int)wcslen(filename) + /* (int)wcslen(L"/") */ + 1 + 1));
                        wcscat(wcpcpy(wcpcpy(destFullFilename, pStVarTwoExpanded), L"/"), filename);

                        ierrCopy = CopyFileFunction(destFullFilename, pStVarOneExpanded);

                        FREE(filename);
                        FREE(destFullFilename);
                    }
                    else
                    {
                        FREE(pStVarOneExpanded);
                        FREE(pStVarTwoExpanded);
                        Scierror(1);
                        return 0;
                    }
                }
                else
                {
                    /* copy a file into a file */
                    ierrCopy = CopyFileFunction(pStVarTwoExpanded, pStVarOneExpanded);
                }
            }
            else
            {
                FREE(pStVarOneExpanded);
                FREE(pStVarTwoExpanded);
                Scierror(110, 1, _("valid filename or directory"));
                return 1;
            }
        }
        else
        {
            FREE(pStVarOneExpanded);
            FREE(pStVarTwoExpanded);
            Scierror(999, _("%s: Wrong value(s) for input argument(s).\n"), fname);
            return 0;
        }

        returnCopyFileResultOnStack(ierrCopy, fname, pvApiCtx);
    }
    else
    {
        FREE(pStVarOneExpanded);
        FREE(pStVarTwoExpanded);
        Scierror(110, 1, _("valid filename or directory"));
        return 1;
    }

    FREE(pStVarOneExpanded);
    FREE(pStVarTwoExpanded);

    return 0;
}

/*--------------------------------------------------------------------------*/
static wchar_t *getFilenameWithExtension(wchar_t * wcFullFilename)
{
    wchar_t *wcfilename = NULL;

    if (wcFullFilename)
    {
        size_t size_wcFullFilename = sizeof(wchar_t) * (wcslen(wcFullFilename) + 1);

        wchar_t *wcname = (wchar_t *)MALLOC(size_wcFullFilename);
        wchar_t *wcext = (wchar_t *)MALLOC(size_wcFullFilename);

        wcfilename = (wchar_t *)MALLOC(size_wcFullFilename);

        if (wcname == NULL || wcext == NULL || wcfilename == NULL)
        {
            FREE(wcname);
            FREE(wcext);
            FREE(wcfilename);
            return NULL;
        }

        splitpathW(wcFullFilename, FALSE, NULL, NULL, wcname, wcext);

        wcscat(wcpcpy(wcfilename, wcname), wcext);

        FREE(wcname);
        FREE(wcext);
    }
    return wcfilename;
}
/*--------------------------------------------------------------------------*/
static int returnCopyFileResultOnStack(int ierr, char *fname, void* pvApiCtx)
{
    double dError = 0.;
    wchar_t *sciError = NULL;

#ifdef _MSC_VER
    if (ierr)
    {
#define BUFFER_SIZE 1024
        DWORD dw = GetLastError();
        wchar_t buffer[BUFFER_SIZE];

        if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
                           dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, BUFFER_SIZE, NULL) == 0)
        {
            wcscpy(buffer, L"Unknown Error");
        }

        // Compatibility with previous version , we return 0
        //dError = (double) dw;
        dError = (double)0.;

        sciError = (wchar_t *) MALLOC(sizeof(wchar_t) * ((int)wcslen(buffer) + 1));
        if (sciError == NULL)
        {
            Scierror(1);
            return 0;
        }

        wcscpy(sciError, buffer);
    }
    else
    {
        dError = 1.;
        sciError = (wchar_t *) MALLOC(sizeof(wchar_t) * 1);
        if (sciError == NULL)
        {
            Scierror(1);
            return 0;
        }
        wcscpy(sciError, L"");
    }
#else
    if (ierr)
    {
        // Compatibility with previous version , we return 0
        //dError = (double) ierr;
        //dError = (double) 0.;
        sciError = to_wide_string(strerror(errno));
        if (sciError == NULL)
        {
            Scierror(1);
            return 0;
        }
    }
    else
    {
        dError = 1.;
        sciError = (wchar_t *) MALLOC(sizeof(wchar_t) * 1);
        if (sciError == NULL)
        {
            Scierror(1);
            return 0;
        }
        wcscpy(sciError, L"");
    }
#endif

    if (createScalarDouble(pvApiCtx, Rhs + 1, dError))
    {
        if (sciError)
        {
            FREE(sciError);
            sciError = NULL;
        }
        return 0;
    }

    LhsVar(1) = Rhs + 1;

    if (Lhs == 2)
    {
        if (createSingleWideString(pvApiCtx, Rhs + 2, sciError))
        {
            if (sciError)
            {
                FREE(sciError);
                sciError = NULL;
            }
            return 0;
        }
        LhsVar(2) = Rhs + 2;
    }

    if (sciError)
    {
        FREE(sciError);
        sciError = NULL;
    }

    PutLhsVar();
    return 0;
}

/*--------------------------------------------------------------------------*/
