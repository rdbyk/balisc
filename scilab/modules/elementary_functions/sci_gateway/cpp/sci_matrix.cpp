/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - DIGITEO - Cedric DELAMARRE
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2020 Dirk Reusch, Kybernetik Dr. Reusch
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
#include "string.hxx"
#include "struct.hxx"
#include "cell.hxx"
#include "overload.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Cell;
using types::Double;
using types::Function;
using types::GenericType;
using types::Struct;
using types::typed_list;

static const char fname[] = "matrix";

Function::ReturnValue sci_matrix(typed_list &in, int _iRetCount, typed_list &out)
{
    int* piSizes    = NULL;
    int iDims       = 0;
    int iLeastOne   = -1;
    int newSize     = 1;
    bool bOk        = false;

    if (in.size() < 2 || in.size() > MAX_DIMS + 1)
    {
        Scierror(72, 2, MAX_DIMS + 1);
        return Function::Error;
    }

    if (in[0]->isArrayOf()      == false &&
        in[0]->isSparse()       == false &&
        in[0]->isSparseBool()   == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_matrix";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    GenericType* pGTIn = in[0]->getAs<GenericType>();

    if ((pGTIn->isSparse() || pGTIn->isSparseBool()) && in.size() > 3)
    {
        Scierror(72, 2, 3);
        return Function::Error;
    }

    if (pGTIn->getSize() == 0)
    {
        out.push_back(pGTIn->clone());
        return Function::OK;
    }

    if (in.size() == 2)
    {
        if (in[1]->isDouble() == false)
        {
            Scierror(94, 2);
            return Function::Error;
        }

        Double* pDblNewSize = in[1]->getAs<Double>();

        if (pDblNewSize->isComplex())
        {
            Scierror(94, 2);
            return Function::Error;
        }

        iDims = pDblNewSize->getSize();
        piSizes = new int[iDims];

        for (int i = 0; i < iDims; i++)
        {
            piSizes[i] = static_cast<int>(pDblNewSize->get(i));
            if (piSizes[i] == -1)
            {
                if (iLeastOne == -1)
                {
                    iLeastOne = i;
                }
                else
                {
                    Scierror(110, 2, _("only one value -1"));
                    delete[] piSizes;
                    return Function::Error;
                }
            }
            else if (piSizes[i] < -1)
            {
                Scierror(110, 2, _("value <= -1"));
                delete[] piSizes;
                return Function::Error;
            }
            else
            {
                newSize *= piSizes[i];
            }
        }
    }
    else
    {
        iDims = static_cast<int>(in.size()) - 1;
        piSizes = new int[iDims];
        for (int i = 1; i < static_cast<int>(in.size()); i++)
        {
            if (in[i]->isDouble() == false)
            {
                Scierror(93, i + 1);
                delete[] piSizes;
                return Function::Error;
            }

            Double* pDblNewSize = in[i]->getAs<Double>();

            if (pDblNewSize->isComplex() || pDblNewSize->isScalar() == false)
            {
                Scierror(93, i + 1);
                delete[] piSizes;
                return Function::Error;
            }

            piSizes[i - 1] = static_cast<int>(pDblNewSize->getFirst());
            if (piSizes[i - 1] == -1)
            {
                if (iLeastOne == -1)
                {
                    iLeastOne = i - 1;
                }
                else
                {
                    Scierror(110, i + 1, _("only one value -1"));
                    delete[] piSizes;
                    return Function::Error;
                }
            }
            else if (piSizes[i - 1] < -1)
            {
                Scierror(110, i + 1, _("value <= -1"));
                delete[] piSizes;
                return Function::Error;
            }
            else
            {
                newSize *= piSizes[i - 1];
            }
        }
    }

    if (iLeastOne != -1)
    {
        piSizes[iLeastOne] = (int)pGTIn->getSize() / newSize;
    }

    if (pGTIn->isSparse() || pGTIn->isSparseBool())
    {
        if (iDims > 2)
        {
            Scierror(110, 2, _("vector with at most 2 elements"));
            delete[] piSizes;
            return Function::Error;
        }
    }
    else if (iDims > MAX_DIMS)
    {
        if (iDims > 2)
        {
            Scierror(110, 2, _("vector with at most 32 elements"));
            delete[] piSizes;
            return Function::Error;
        }
    }

    GenericType* pGTOut = pGTIn->getRef() > 1 ? pGTIn->clone()->getAs<GenericType>() : pGTIn;

    bOk = pGTOut->reshape(piSizes, iDims);
    delete[] piSizes;

    if (bOk == false)
    {
        Scierror(999, _("%s: Input and output matrices must have the same number of elements.\n"), fname);
        pGTOut->killMe();
        return Function::Error;
    }

    out.push_back(pGTOut);
    return Function::OK;
}
