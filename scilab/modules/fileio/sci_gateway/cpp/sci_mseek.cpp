/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Allan CORNET
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2011 - DIGITEO - Cedric DELAMARRE
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

#include "filemanager.hxx"
#include "fileio_gw.hxx"
#include "string.hxx"
#include "double.hxx"
#include "bool.hxx"
#include "function.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
#include "mseek.h"
}

#if (defined(sun) && !defined(SYSV))
char *strerror (int errcode);
#endif

#if (defined(sun) && !defined(SYSV)) || defined(sgi)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

types::Function::ReturnValue sci_mseek(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int iFile           = -1; //default file : last opened file
    int iRet            = 0;
    long long iWhere    = 0;
    int iFlag           = 0;
    wchar_t* wcsFlag    = NULL;

    if (in.size() < 1 || in.size() > 3)
    {
        Scierror(72, 1, 3);
        return types::Function::Error;
    }

    if (in[0]->isDouble() == false || in[0]->getAs<types::Double>()->isScalar() == false || in[0]->getAs<types::Double>()->isComplex())
    {
        Scierror(93, 1);
        return types::Function::Error;
    }

    iWhere = static_cast<long long>(in[0]->getAs<types::Double>()->getFirst());

    if (in.size() == 2)
    {
        if (in[1]->isDouble() && in[1]->getAs<types::Double>()->isScalar() && in[1]->getAs<types::Double>()->isComplex() == false)
        {
            iFile = static_cast<int>(in[1]->getAs<types::Double>()->getFirst());
        }
        else if (in[1]->isString() && in[1]->getAs<types::String>()->isScalar())
        {
            wcsFlag = in[1]->getAs<types::String>()->getFirst();
        }
        else
        {
            Scierror(93, 2, _("real scalar or string"));
            return types::Function::Error;
        }
    }

    if (in.size() == 3)
    {
        if (in[1]->isDouble() == false || in[1]->getAs<types::Double>()->isScalar() == false || in[1]->getAs<types::Double>()->isComplex())
        {
            Scierror(93, 2);
            return types::Function::Error;
        }
        if (in[2]->isString() == false || in[2]->getAs<types::String>()->isScalar() == false)
        {
            Scierror(91, 3);
            return types::Function::Error;
        }

        iFile = static_cast<int>(in[1]->getAs<types::Double>()->getFirst());
        wcsFlag = in[2]->getAs<types::String>()->getFirst();
    }

    switch (iFile)
    {
        case 0: // stderr
        case 5: // stdin
        case 6: // stdout
            Scierror(30, iFile);
            return types::Function::Error;
    }

    if (wcsFlag != NULL)
    {
        if (wcsncmp(wcsFlag, L"set", 3) == 0)
        {
            iFlag = SEEK_SET;
        }
        else if (wcsncmp(wcsFlag, L"cur", 3) == 0)
        {
            iFlag = SEEK_CUR;
        }
        else if (wcsncmp(wcsFlag, L"end", 3) == 0)
        {
            iFlag = SEEK_END;
        }
        else
        {
            Scierror(110, 3, _("'set', 'cur', or 'end'"));
            return types::Function::Error;
        }
    }
    else
    {
        iFlag = SEEK_SET;
    }

    int iErr = mseek(iFile, iWhere, iFlag);

    out.push_back(new types::Bool(!iErr));
    return types::Function::OK;
}
