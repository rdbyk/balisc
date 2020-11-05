/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011-2011 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2014 - Scilab Enterprises - Anais AUBERT
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - 2020 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "core_gw.hxx"
#include "types.hxx"
#include "function.hxx"
#include "double.hxx"
#include "string.hxx"
#include "overload.hxx"
#include "configvariable.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "localization.h"
#include "Scierror.h"
#include "charEncoding.h"
#include "lasterror.h"
}

#include "errmsgs.h"

using types::Callable;
using types::Double;
using types::Function;
using types::String;
using types::typed_list;

#define UNKNOWN_ERROR_CODE 0
#define DEFAULT_ERROR_CODE 10000

Function::ReturnValue sci_error(typed_list &in, int _iRetCount, typed_list &out)
{
    int iErrorCode = DEFAULT_ERROR_CODE;

    if (_iRetCount > 1)
    {
        Scierror(81, 1);
        return Function::Error;
    }

    if (in.empty())
    {
        iErrorCode = UNKNOWN_ERROR_CODE;
    }

    if (in.size() >= 1 && in[0]->isString() == false && in[0]->isDouble() == false)
    {
        Scierror(90, 1, _("real scalar or a string"));
        return Function::Error;
    }

    if (in.size() >= 1 && in[0]->isDouble())
    {
        Double* pDbl = in[0]->getAs<Double>();

        if (pDbl->isComplex())
        {
            Scierror(93, 1);
            return Function::Error;
        }

        if (pDbl->isScalar() == false)
        {
            Scierror(101, 1);
            return Function::Error;
        }

        if (pDbl->getFirst() < 0)
        {
            Scierror(110, 1, _("non-negative real value"));
            return Function::Error;
        }

        iErrorCode = (int) pDbl->getFirst();
        in.erase(in.begin());
    }

    Callable::ReturnValue ret;
    typed_list msprintf_out;

    char *predefErrorMsg = ErrorMessageByNumber(iErrorCode);

    if (predefErrorMsg)
    {
        typed_list msprintf_in;
        const std::vector<ConfigVariable::WhereEntry>& where = ConfigVariable::getWhere();

        if (where.size() > 1)
        {
            std::string fmt("%s: ");
            fmt += predefErrorMsg;
            msprintf_in.push_back(new String(fmt.c_str()));
            msprintf_in.push_back(new String((++where.rbegin())->call->getName().c_str()));
        }
        else
        {
            msprintf_in.push_back(new String(predefErrorMsg));
        }

        // remaining args
        for (int i = 0; i < in.size(); ++i)
        {
            msprintf_in.push_back(in[i]);
        }

        ret = Overload::call(L"msprintf", msprintf_in, 1, msprintf_out);

        delete msprintf_in[0];
        if (where.size() > 1)
        {
            delete msprintf_in[1];
        }

        if (ret != Callable::OK)
        {
            char* f = os_strdup(predefErrorMsg);
            int n = strlen(f);
            if (n && f[n-1] == '\n') f[n-1] = '\0'; // strip trailing \n
            Scierror(62, f);
            FREE(f);
            return Function::Error;
        }
    }
    else
    {
        // user defined error
        if (in[0]->isString() && in[0]->getAs<String>()->getSize() >= 1)
        {
            typed_list msprintf_in = in;
            String* pFormatArg = msprintf_in[0]->getAs<String>();

            std::wstring fmt = pFormatArg->getFirst();

            for (int i = 1; i < pFormatArg->getSize(); ++i)
            {
                fmt += L"\n";
                fmt += pFormatArg->get(i);
            }

            msprintf_in[0] = new String(fmt.c_str());
            ret = Overload::call(L"msprintf", msprintf_in, 1, msprintf_out);
            delete msprintf_in[0];

            if (ret != Callable::OK)
            {
                char *f = wide_string_to_UTF8(fmt.c_str());
                Scierror(62, f);
                FREE(f);
                return Function::Error;
            }
        }
        else
        {
            Scierror(63, iErrorCode);
            return Function::Error;
        }
    }

    String* pStrError = msprintf_out[0]->getAs<String>();

    std::wstring wstrErr = L"";

    for (int i = 0; i < pStrError->getSize(); i++)
    {
        wstrErr.append(pStrError->get(i));

        if (i < pStrError->getSize() - 1)
        {
            wstrErr.append(L"\n");
        }
    }

    setLastError(iErrorCode, wstrErr.c_str(), 0, NULL);

    return Function::Error;
}
