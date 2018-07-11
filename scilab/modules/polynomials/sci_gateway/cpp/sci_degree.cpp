/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - Scilab Enterprises - Cedric DELAMARRE
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

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

types::Function::ReturnValue sci_degree(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::Double* pDblOut = NULL;

    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d expected.\n"), "degree", 1);
        return types::Function::Error;
    }

    if (in[0]->isDouble())
    {
        types::Double* pDblIn = in[0]->getAs<types::Double>();
        double *pReal = pDblIn->get();
        pDblOut = new types::Double(pDblIn->getDims(), pDblIn->getDimsArray());
        double* pdblOut = pDblOut->get();
        if (pDblIn->isComplex())
        {
            double *pImg = pDblIn->getImg();
            for (int i = 0; i < pDblOut->getSize(); i++)
            {
                pdblOut[i] = pReal[i]==0 && pImg[i]==0 ? -INFINITY : 0;;
            }
        }
        else
        {
            for (int i = 0; i < pDblOut->getSize(); i++)
            {
                pdblOut[i] = pReal[i]==0 ? -INFINITY : 0;
            }
        }
    }
    else if (in[0]->isPoly())
    {
        types::Polynom* pPolyIn = in[0]->getAs<types::Polynom>();
        pDblOut = new types::Double(pPolyIn->getDims(), pPolyIn->getDimsArray());
        double* pdblOut = pDblOut->get();

        for (int i = 0; i < pDblOut->getSize(); i++)
        {
            pdblOut[i] = pPolyIn->get(i)->getDegree();
        }
    }
    else
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_degree";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    out.push_back(pDblOut);
    return types::Function::OK;
}
