/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "function.hxx"
#include "string.hxx"
#include "double.hxx"
#include "filemanager.hxx"
#include "fileio_gw.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "Scierror.h"
#include "localization.h"
#include "mclose.h"
}
#include "stdio.h"

static const char fname[] = "mclose";

types::Function::ReturnValue sci_mclose(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int iRet = 0;
    if (in.size() == 0)
    {
        //close current file
        iRet = mcloseCurrentFile();
    }
    else if (in.size() == 1)
    {
        if (in[0]->isString())
        {
            types::String *pS = in[0]->getAs<types::String>();
            if (pS->getSize() != 1)
            {
                Scierror(91, 1);
                return types::Function::Error;
            }

            if (FileManager::isOpened(pS->getFirst()))
            {
                int iFileID = FileManager::getFileID(pS->getFirst());
                if (iFileID == -1)
                {
                    char* pst = wide_string_to_UTF8(pS->getFirst());
                    Scierror(999, _("%s: File not found: '%s'.\n"), fname, pst);
                    FREE(pst);
                    return types::Function::Error;
                }
                iRet = mclose(iFileID);
            }
            else if (wcscmp(pS->getFirst(), L"all") == 0)
            {
                iRet = mcloseAll();
            }
            else
            {
                Scierror(110, 1, "'all'");
                return types::Function::Error;
            }
        }
        else if (in[0]->isDouble())
        {
            types::Double* pD = in[0]->getAs<types::Double>();
            if (pD->getSize() != 1 || pD->isComplex())
            {
                Scierror(93, 1);
                return types::Function::Error;
            }

            int iVal = static_cast<int>(pD->getFirst());
            switch (iVal)
            {
                case 0: // stderr
                case 5: // stdin
                case 6: // stdout
                    Scierror(50, iVal);
                    return types::Function::Error;
            }
            iRet = mclose(iVal);
        }
        else
        {
            Scierror(90, 1, _("integer or string"));
            return types::Function::Error;
        }
    }
    else
    {
        Scierror(72, 0, 1);
        return types::Function::Error;
    }

    types::Double* pD = new types::Double(static_cast<double>(iRet));
    out.push_back(pD);
    return types::Function::OK;
}
