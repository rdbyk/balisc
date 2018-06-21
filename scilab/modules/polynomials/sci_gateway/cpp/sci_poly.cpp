/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Cedric DELAMARRE
 * Copyright (C) 2015 - Scilab Enterprises - Anais AUBERT
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

#include "polynomials_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "string.hxx"
#include "polynom.hxx"
#include "overload.hxx"
#include "context.hxx"
#include "execvisitor.hxx"

extern "C"
{
#include <math.h>
#include "Scierror.h"
#include "localization.h"
#include "elem_common.h"
extern int C2F(dprxc)(int*, double*, double*);
extern int C2F(wprxc)(int*, double*, double*, double*, double*);
}

using types::Double;
using types::Function;
using types::Polynom;
using types::String;
using types::optional_list;
using types::typed_list;
using symbol::Context;

static const char fname[] = "poly";

Function::ReturnValue sci_poly(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() < 2 || in.size() > 3)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d to %d expected.\n"), fname, 2, 3);
        return Function::Error;
    }

    if (in[0]->isDouble() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_poly";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    Double* pDblIn = in[0]->getAs<Double>();
    std::wstring wstrFlag = L"roots"; // roots (default), coeff

    if (in.size() == 3)
    {
        if (in[2]->isString() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d : string expected.\n"), fname, 3);
            return Function::Error;
        }

        wstrFlag = in[2]->getAs<String>()->getFirst();

        if (wstrFlag != L"roots" && wstrFlag != L"coeff" && wstrFlag != L"r" && wstrFlag != L"c")
        {
            Scierror(999, _("%s: Wrong value for input argument #%d : ""%s"" or ""%s"" expected.\n"), fname, 3, "roots", "coeff");
            return Function::Error;
        }
    }

    if (in[1]->isString() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d : string expected.\n"), fname, 2);
        return Function::Error;
    }

    String* pStrName = in[1]->getAs<String>();

    if (pStrName->isScalar() == false)
    {
        Scierror(999, _("%s: Wrong size for input argument #%d : A scalar expected.\n"), fname, 2);
        return Function::Error;
    }

    wchar_t* wcsName = pStrName->getFirst();

    if (Context::getInstance()->isValidVariableName(wcsName) == false)
    {
        char* pstrName = wide_string_to_UTF8(wcsName);
        Scierror(999, _("%s: Wrong value \"%s\" in argument #%d: A valid variable name expected.\n"), fname, pstrName, 2);
        FREE(pstrName);
        return Function::Error;
    }

    Polynom* pPolyOut = NULL;

    if (wstrFlag == L"roots" || wstrFlag == L"r") // roots
    {
        // [] case
        if (pDblIn->getSize() == 0)
        {
            int *iRank = new int[1];
            *iRank = 0;
            Polynom* pPolyOut = new Polynom(wcsName, 1, 1, iRank);
            delete[] iRank;
            double* pdblCoef = pPolyOut->getFirst()->get();
            *pdblCoef = 1;
            out.push_back(pPolyOut);
            return Function::OK;
        }

        bool bDeleteInput = false;
        bool bComplexResult = pDblIn->isComplex();

        if (pDblIn->getSize() != 1 && pDblIn->getCols() == pDblIn->getRows())
        {
            //call spec
            typed_list tlInput;
            typed_list tlOutput;
            optional_list tlOpt;
            tlInput.push_back(pDblIn);
            Function *funcSpec = symbol::Context::getInstance()->get(symbol::Symbol(L"spec"))->getAs<Function>();
            funcSpec->call(tlInput, tlOpt, 1, tlOutput);
            pDblIn = tlOutput[0]->getAs<Double>();
            bDeleteInput = true;
        }

        int iOne = 1;
        double* pdblInReal = pDblIn->get();
        int piDimsArray[2] = {1, 1};
        int iSize = pDblIn->getSize();
        int *iRanks = new int[1];
        *iRanks = iSize;
        pPolyOut = new Polynom(wcsName, 2, piDimsArray, iRanks);
        double* pdblCoefReal = pPolyOut->getFirst()->get();

        if (pDblIn->isComplex())
        {
            pPolyOut->setComplex(true);
            double* pdblInImg   = pDblIn->getImg();
            double* pdblCoefImg = pPolyOut->getFirst()->getImg();
            C2F(wprxc)(iRanks, pdblInReal, pdblInImg, pdblCoefReal, pdblCoefImg);
            pPolyOut->setComplex(bComplexResult);
        }
        else
        {
            C2F(dprxc)(iRanks, pdblInReal, pdblCoefReal);
        }
        delete[] iRanks;

        if (bDeleteInput)
        {
            delete pDblIn;
        }
    }
    else // coeff
    {
        // [] case
        if (pDblIn->getSize() == 0)
        {
            out.push_back(Double::Empty());
            return Function::OK;
        }

        if (pDblIn->getRows() != 1 && pDblIn->getCols() != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d : A vector expected.\n"), fname, 1);
            return Function::Error;
        }

        int piDimsArray[2] = {1, 1};
        int *iRanks = new int[1];
        *iRanks = pDblIn->getSize() - 1;
        pPolyOut = new Polynom(wcsName, 2, piDimsArray, iRanks);
        delete[] iRanks;
        pPolyOut->setComplex(pDblIn->isComplex());
        pPolyOut->setCoef(0, pDblIn);
        pPolyOut->updateRank();
    }

    pPolyOut->updateRank();
    out.push_back(pPolyOut);
    return Function::OK;
}
