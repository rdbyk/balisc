/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - DIGITEO - Cedric DELAMARRE
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

#include <cmath>

#include "elem_func_gw.hxx"
#include "double.hxx"
#include "int.hxx"
#include "function.hxx"
#include "overload.hxx"
#include "polynom.hxx"

#include "abs.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

template <class T>
T* absInt(T* _pIn)
{
    T* pIntOut = new T(_pIn->getDims(), _pIn->getDimsArray());
    int size = _pIn->getSize();

    typename T::type* pI = _pIn->get();
    typename T::type* pO = pIntOut->get();
    for (int i = 0; i < size; i++)
    {
        pO[i] = std::abs(pI[i]);
    }

    return pIntOut;
}

types::Function::ReturnValue sci_abs(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d expected.\n"), "abs", 1);
        return types::Function::Error;
    }

    switch (in[0]->getType())
    {
        case types::InternalType::ScilabDouble:
        {
            out.push_back(balisc::abs(in[0]->getAs<types::Double>()));
            break;
        }
        case types::InternalType::ScilabPolynom:
        {
            types::Polynom* pPolyIn = in[0]->getAs<types::Polynom>();
            types::Polynom* pPolyOut = new types::Polynom(pPolyIn->getVariableName(), pPolyIn->getDims(), pPolyIn->getDimsArray());
            double* data = NULL;

            if (pPolyIn->isComplex())
            {
                for (int i = 0; i < pPolyIn->getSize(); i++)
                {
                    int rank = pPolyIn->get(i)->getRank();
                    types::SinglePoly* pSP = new types::SinglePoly(&data, rank);

                    for (int j = 0; j < rank + 1; j++)
                    {
                        data[j] = hypot(pPolyIn->get(i)->get()[j], pPolyIn->get(i)->getImg()[j]);
                    }

                    pPolyOut->set(i, pSP);
                    delete pSP;
                    pSP = NULL;
                }
            }
            else
            {
                for (int i = 0; i < pPolyIn->getSize(); i++)
                {
                    int rank = pPolyIn->get(i)->getRank();
                    types::SinglePoly* pSP = new types::SinglePoly(&data, rank);

                    for (int j = 0; j < rank + 1; j++)
                    {
                        data[j] = std::fabs(pPolyIn->get(i)->get()[j]);
                    }

                    pPolyOut->set(i, pSP);
                    delete pSP;
                    pSP = NULL;
                }
            }

            out.push_back(pPolyOut);
            break;
        }
        case types::InternalType::ScilabInt8:
        {
            out.push_back(absInt(in[0]->getAs<types::Int8>()));
            break;
        }
        case types::InternalType::ScilabInt16:
        {
            out.push_back(absInt(in[0]->getAs<types::Int16>()));
            break;
        }
        case types::InternalType::ScilabInt32:
        {
            out.push_back(absInt(in[0]->getAs<types::Int32>()));
            break;
        }
        case types::InternalType::ScilabInt64:
        {
            out.push_back(absInt(in[0]->getAs<types::Int64>()));
            break;
        }
        case types::InternalType::ScilabUInt8:
        case types::InternalType::ScilabUInt16:
        case types::InternalType::ScilabUInt32:
        case types::InternalType::ScilabUInt64:
        {
            out.push_back(in[0]);
            break;
        }
        default:
        {
            std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_abs";
            return Overload::call(wstFuncName, in, _iRetCount, out);
        }
    }

    return types::Function::OK;
}
