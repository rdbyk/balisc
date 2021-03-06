/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Allan CORNET
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
#include "sci_malloc.h"
#include "mputl.h"
#include "localization.h"
#include "Scierror.h"
#include "mopen.h"
#include "mclose.h"
#include "expandPathVariable.h"
}

types::Function::ReturnValue sci_mputl(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int iFileID     = 0;
    int iErr        = 0;
    bool bCloseFile = false;

    if (in.size() != 2)
    {
        Scierror(71, 2);
        return types::Function::Error;
    }

    if (in[1]->isDouble() && in[1]->getAs<types::Double>()->getSize() == 1)
    {
        iFileID = static_cast<int>(in[1]->getAs<types::Double>()->getFirst());
    }
    else if (in[1]->isString() && in[1]->getAs<types::String>()->getSize() == 1)
    {
        wchar_t *expandedFileName = expandPathVariableW(in[1]->getAs<types::String>()->getFirst());

        iErr = mopen(expandedFileName, L"wt", 0, &iFileID);
        FREE(expandedFileName);

        if (iErr)
        {
            char* pst = wide_string_to_UTF8(in[1]->getAs<types::String>()->getFirst());
            switch (iErr)
            {
                case MOPEN_NO_MORE_LOGICAL_UNIT:
                    Scierror(53);
                    break;
                case MOPEN_CAN_NOT_OPEN_FILE:
                    Scierror(52, pst);
                    break;
                case MOPEN_NO_MORE_MEMORY:
                    Scierror(1);
                    break;
                case MOPEN_INVALID_FILENAME:
                    Scierror(54, pst);
                    break;
                default: //MOPEN_INVALID_STATUS
                    Scierror(55);
                    break;
            }
            FREE(pst);
            return types::Function::Error;
        }

        bCloseFile = true;
    }
    else
    {
        //Error
        Scierror(90, 2, _("%string or integer"));
        return types::Function::Error;
    }

    //String vextor, row or col
    if (in[0]->isString() == false || (in[0]->getAs<types::String>()->getRows() != 1 && in[0]->getAs<types::String>()->getCols() != 1))
    {
        Scierror(100, _("1-by-n or m-by-1 array"));
        return types::Function::Error;
    }

    types::String* pS = in[0]->getAs<types::String>();

    switch (iFileID)
    {
        case 5: // stdin
            Scierror(50, iFileID);
            return types::Function::Error;
        default :
            iErr = mputl(iFileID, pS->get(), pS->getSize());
    }

    out.push_back(new types::Bool(!iErr));

    if (bCloseFile)
    {
        mclose(iFileID);
    }

    return types::Function::OK;
}
