/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2017 - Scilab Enterprises - ELIAS Antoine
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

#include "output_stream_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "double.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "expandPathVariable.h"
#include "mopen.h"
#include "mclose.h"
#include "mputl.h"
#include "sci_malloc.h"
}

types::Function::ReturnValue sci_print(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int fid = 0;
    bool bCloseFile = false;
    wchar_t* newLine = L"";

    if (in.size() <= 1)
    {
        Scierror(74, 2);
        return types::Function::Error;
    }

    if (in[0]->isString())
    {
        types::String* pS = in[0]->getAs<types::String>();
        if (pS->isScalar() == false)
        {
            Scierror(102, 1);
            return types::Function::Error;
        }

        wchar_t *expandedFileName = expandPathVariableW(in[0]->getAs<types::String>()->getFirst());

        int iErr = mopen(expandedFileName, L"wt", 0, &fid);

        if (iErr)
        {
            char* pst = wide_string_to_UTF8(expandedFileName);
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
            FREE(expandedFileName);
            return types::Function::Error;
        }
        FREE(expandedFileName);
        bCloseFile = true;

    }
    else if (in[0]->isDouble())
    {
        types::Double* pD = in[0]->getAs<types::Double>();
        if (pD->isScalar() == false)
        {
            Scierror(101, 1);
            return types::Function::Error;
        }

        fid = static_cast<int>(pD->get()[0]);
        //stdin
        if (fid == 5)
        {
            Scierror(50, fid);
            return types::Function::Error;
        }
    }
    else
    {
        Scierror(90, 1, _("real or string"));
        return types::Function::Error;
    }

    mputl(fid, &newLine, 1);
    for (int i = (int)in.size() - 1; i > 0 ; --i)
    {
        std::wostringstream ostr;
        in[i]->toString(ostr);
        wchar_t* tmp = os_wcsdup(ostr.str().c_str());
        mputl(fid, &tmp, 1);
        FREE(tmp);
    }

    if (bCloseFile)
    {
        mclose(fid);
    }

    return types::Function::OK;
}
