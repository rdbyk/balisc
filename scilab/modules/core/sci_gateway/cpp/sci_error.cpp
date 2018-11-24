/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011-2011 - DIGITEO - Bruno JOFRET
 * Copyright (C) 2014 - Scilab Enterprises - Anais AUBERT
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
}

using types::Callable;
using types::Double;
using types::Function;
using types::String;
using types::typed_list;

#define DEFAULT_ERROR_CODE 10000

static const char fname[] = "error";

Function::ReturnValue sci_error(typed_list &in, int _iRetCount, typed_list &out)
{
    int iErrorCode = DEFAULT_ERROR_CODE;
    String* pStrError = NULL;

    if (_iRetCount > 1)
    {
        Scierror(78, _("%s: Wrong number of output arguments: %d expected.\n"), fname, 1);
        return Function::Error;
    }

    if (in.empty())
    {
        Scierror(77, _("%s: Wrong number of input arguments: At least %d expected.\n"), fname, 1, 2);
        return Function::Error;
    }

    if (in.size() == 1 && in[0]->isString() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), fname, 1);
        return Function::Error;
    }

    if (in.size() > 1 && in[0]->isDouble())
    {
        Double* pDbl = in[0]->getAs<Double>();

        if (pDbl->isComplex())
        {
            Scierror(999, _("%s: Wrong type for input argument #%d.\n"), fname, 1);
            return Function::Error;
        }

        if (pDbl->isScalar() == false)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d.\n"), fname, 1);
            return Function::Error;
        }

        if (pDbl->getFirst() <= 0)
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: Value greater than 0 expected.\n"), fname, 1);
            return Function::Error;
        }

        iErrorCode = (int) pDbl->getFirst();

        in.erase(in.begin());
    }

    Callable::ReturnValue ret;
    typed_list msprintf_out;

    if (in[0]->isString() && in[0]->getAs<String>()->getSize() > 1)
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
    }
    else
    {
        ret = Overload::call(L"msprintf", in, 1, msprintf_out);
    }

    if (ret != Callable::OK)
    {
        ConfigVariable::setLastErrorMessage(L"error: "+ ConfigVariable::getLastErrorMessage());
        return ret;
    }

    pStrError = msprintf_out[0]->getAs<String>();

    std::string strErr = "";

    for (int i = 0; i < pStrError->getSize(); i++)
    {
        char *pstErrorLine = wide_string_to_UTF8(pStrError->get(i));

        strErr.append(pstErrorLine);

        if (i < pStrError->getSize() - 1)
        {
            strErr.append("\n");
        }

        FREE(pstErrorLine);
    }

    Scierror(iErrorCode, "%s", strErr.c_str());

    return Function::Error;
}
