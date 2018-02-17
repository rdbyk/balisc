/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2014 - Scilab Enterprises - Sylvain Genin
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

#include "elem_func_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "polynom.hxx"
#include "overload.hxx"
#include "round.hxx"

extern "C"
{
#include "Scierror.h"
}

types::Function::ReturnValue sci_round(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): At least %d expected.\n"), "round", 1);
        return types::Function::Error;
    }

    if (in[0]->isDouble())
    {
        out.push_back(balisc::round(in[0]->getAs<types::Double>()));
        return types::Function::OK;
    }
    else if (in[0]->isPoly())
    {
        /***** get data *****/
        types::Polynom* pPolyIn = in[0]->getAs<types::Polynom>();
        int* piRankPolyIn = new int[pPolyIn->getSize()];
        pPolyIn->getRank(piRankPolyIn);

        types::Polynom* pPolyOut = new types::Polynom(pPolyIn->getVariableName(), pPolyIn->getDims(), pPolyIn->getDimsArray(), piRankPolyIn);
        pPolyOut->setComplex(pPolyIn->isComplex());

        /***** perform operation *****/
        for (int compterElem = 0; compterElem < pPolyIn->getSize(); compterElem++)
        {
            types::SinglePoly* pSPIn  = pPolyIn->get(compterElem);
            types::SinglePoly* pSPOut = pPolyOut->get(compterElem);

            double* pRealIn  = pSPIn->get();
            double* pRealOut = pSPOut->get();

            if (pPolyIn->isComplex())
            {
                double* pImgIn  = pSPIn->getImg();
                double* pImgOut = pSPOut->getImg();
                for (int i = 0; i < piRankPolyIn[compterElem] + 1; i++)
                {
                    pRealOut[i] = std::round(pRealIn[i]);
                    pImgOut[i]  = std::round(pImgIn[i]);
                }
            }
            else
            {
                for (int i = 0; i < piRankPolyIn[compterElem] + 1; i++)
                {
                    pRealOut[i] = std::round(pRealIn[i]);
                }
            }
        }

        delete[] piRankPolyIn;

        /***** return data *****/
        out.push_back(pPolyOut);
        return types::Function::OK;
    }
    else
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_round";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }
}
