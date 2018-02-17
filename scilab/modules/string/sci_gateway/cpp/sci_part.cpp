/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Allan CORNET , Cong WU
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

#include "string_gw.hxx"
#include "funcmanager.hxx"
#include "function.hxx"
#include "string.hxx"
#include "double.hxx"
#include "overload.hxx"

extern "C"
{
#include <string.h>
#include <stdio.h>
#include "Scierror.h"
#include "localization.h"
#include "freeArrayOfString.h"
}

using types::Double;
using types::Function;
using types::String;
using types::typed_list;

static wchar_t **partfunctionW(wchar_t** _pwstStringInput, const int _iSize, const int *_piVectInput, const int _iVectSize);

static const char fname[] = "part";

Function::ReturnValue sci_part(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 2)
    {
        Scierror(999, _("%s: Wrong number of input argument(s): %d expected.\n"), fname, 2);
        return Function::Error;
    }

    //part([], ...
    if (in[0]->isDouble() && in[0]->getAs<Double>()->isEmpty())
    {
        out.push_back(Double::Empty());
        return Function::OK;
    }

    if (in[0]->isString() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_part";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    String* pS = in[0]->getAs<String>();

    if (in[1]->isDouble() == false)
    {
        std::wstring wstFuncName = L"%"  + in[1]->getShortTypeStr() + L"_part";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    Double* pD = in[1]->getAs<Double>();
    if (pD->isVector() == false && pD->isEmpty() == false)
    {
        //non vector
        Scierror(999, _("%s: Wrong size for input argument #%d: A vector expected.\n"), fname, 2);
        return Function::Error;
    }

    int* piIndex = new int[pD->getSize()];
    for (int i = 0 ; i < pD->getSize() ; i++)
    {
        piIndex[i] = static_cast<int>(pD->getReal()[i]);
        if (piIndex[i] < 1)
        {
            Scierror(36, _("%s: Wrong values for input argument #%d: Must be >= 1.\n"), fname, 2);
            delete[] piIndex;
            return Function::Error;
        }
    }

    wchar_t** pwstOut = partfunctionW(pS->get(), pS->getRows() * pS->getCols(), piIndex, pD->getSize());
    delete[] piIndex;
    String* pOut = new String(pS->getRows(), pS->getCols());
    pOut->set(pwstOut);
    freeArrayOfWideString(pwstOut, pOut->getSize());
    out.push_back(pOut);
    return Function::OK;
}

wchar_t **partfunctionW(wchar_t** _pwstStringInput, const int _iSize, const int *_piVectInput, const int _iVectSize)
{
    wchar_t** pwstParts = (wchar_t**)MALLOC(sizeof(wchar_t*) * (_iSize));

    for (int i = 0; i < _iSize; i++)
    {
        int len_StringInput_i = wcslen(_pwstStringInput[i]);

        pwstParts[i] = (wchar_t*)MALLOC(sizeof(wchar_t) * (_iVectSize + 1));

        for (int j = 0 ; j < _iVectSize ; j++)
        {
            if (_piVectInput[j] > len_StringInput_i)
            {
                pwstParts[i][j] = L' ';
            }
            else
            {
                pwstParts[i][j] = _pwstStringInput[i][_piVectInput[j] - 1];
            }
        }

        pwstParts[i][_iVectSize] = L'\0';
    }

    return pwstParts;
}
