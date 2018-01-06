/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2015 - Scilab Enterprises - Anais AUBERT
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

#include <algorithm>

#include "elem_func_gw.hxx"
#include "types.hxx"
#include "internal.hxx"
#include "double.hxx"
#include "string.hxx"
#include "container.hxx"
#include "overload.hxx"
#include "context.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "os_string.h"
}

static int getMode(types::InternalType* in);

types::Function::ReturnValue sci_size(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() < 1)
    {
        Scierror(999, _("%s: Wrong number of input arguments: At least %d expected.\n"), "size", 1);
        return types::Function::Error;
    }

    switch (in[0]->getType())
    {
        // Dedicated case for lists.
        case types::InternalType::ScilabMList:
        {
            std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_size";
            Overload::call(wstFuncName, in, _iRetCount, out);
            break;
        }
        case types::InternalType::ScilabTList:
        {
            // calls the overload if it exists.
            std::wstring wstFuncName = L"%"  + in[0]->getTypeStr() + L"_size";
            types::InternalType *pIT = symbol::Context::getInstance()->get(symbol::Symbol(wstFuncName));
            if (pIT)
            {
                return Overload::call(wstFuncName, in, _iRetCount, out);
            }
        }
        case types::InternalType::ScilabList:
        {
            if (in.size() > 1)
            {
                Scierror(999, _("%s: Wrong number of input argument(s): %d expected.\n"), "size", 1);
                return types::Function::Error;
            }

            types::Double* pD = new types::Double(in[0]->getAs<types::Container>()->getSize());
            out.push_back(pD);
            break;
        }
        default :
            // All types inherits of GenericType, so have this algorithm as default.
        {
            if (in[0]->isGenericType() == false)
            {
                std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_size";
                return Overload::call(wstFuncName, in, _iRetCount, out);
            }
            int iMode = -1;

            if (in.size() > 2)
            {
                Scierror(77, _("%s: Wrong number of input argument(s): %d to %d expected.\n"), "size", 1, 2);
                return types::Function::Error;
            }

            if (in.size() == 2)
            {
                if (_iRetCount == 2)
                {
                    Scierror(999, _("%s: Wrong number of output argument(s): %d expected.\n"), "size", 1);
                    return types::Function::Error;
                }

                iMode = getMode(in[1]);

                if (iMode == -2)
                {
                    return types::Function::Error;
                }

            }

            int iDims = in[0]->getAs<types::GenericType>()->getDims();
            int* piDims = in[0]->getAs<types::GenericType>()->getDimsArray();

            if (_iRetCount == 1)
            {
                int iRowsOut = 1;
                int iColsOut = 0;
                double* pdblReal = NULL;

                switch (iMode)
                {
                    case -1 : //lhs == 1
                        iColsOut = iDims;
                        break;
                    default : //"*"
                        iColsOut = 1;
                        break;
                }

                types::Double* pD = new types::Double(iRowsOut, iColsOut);

                double* pdbl = pD->getReal();

                switch (iMode)
                {
                    case -1 : //lhs == 1
                        for (int i = 0 ; i < iDims ; i++)
                        {
                            pdbl[i] = piDims[i];
                        }
                        break;
                    case 0 : //"*"
                        pdbl[0] = in[0]->getAs<types::GenericType>()->getSize();
                        break;
                    default : //"r"
                        if (iMode > iDims)
                        {
                            pdbl[0] = 1;
                            out.push_back(pD);
                            return types::Function::OK;
                        }

                        iColsOut = 1;
                        pdbl[0] = piDims[iMode - 1];
                        break;
                }
                out.push_back(pD);
            }
            else
            {
                for (int i = 0 ; i < std::min(_iRetCount, iDims) ; i++)
                {
                    types::Double* pD = new types::Double(piDims[i]);
                    out.push_back(pD);
                }

                /* Multiple returns:
                 * example: [a b c]=size(M) */
                if (_iRetCount > iDims)
                {
                    for (int i = iDims ; i < _iRetCount ; i++)
                    {
                        types::Double* pD = new types::Double(1);
                        out.push_back(pD);
                    }
                }
            }
            break;
        }
    }
    return types::Function::OK;
}

int getMode(types::InternalType* in)
{
    int iMode = 0;

    if (in->isString())
    {
        types::String* pS = in->getAs<types::String>();

        if (pS->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong size for argument %d: (%d,%d) expected.\n"), "size", 2, 1, 1);
        }

        wchar_t * w = pS->getFirst();

        if (w[0] && w[1] == L'\0')
        {
            switch (w[0])
            {
                case 'r':
                    iMode = 1;
                    break;
                case 'c':
                    iMode = 2;
                    break;
                case '*':
                    iMode = 0;
                    break;
                default:
                    Scierror(999, _("%s: Wrong value for input argument #%d: '%s', '%s' or '%s' expected.\n"), "size", 2, "*" , "r", "c");
                    iMode = -2;
                    break;
            }
        }
        else
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: '%s', '%s' or '%s' expected.\n"), "size", 2, "*" , "r", "c");
            iMode = -2;
        }
    }
    else if (in->isDouble() && in->getAs<types::Double>()->isComplex() == false)
    {
        types::Double* pD = in->getAs<types::Double>();

        if (pD->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong size for argument %d: (%d,%d) expected.\n"), "size", 2, 1, 1);
            iMode = -2;
        }
        else
        {
            iMode = static_cast<int>(pD->getReal()[0]);

            if (pD->getReal()[0] != static_cast<double>(iMode))
            {
                Scierror(999, _("%s: Wrong value for input argument #%d: An integer value expected.\n"), "size", 2);
                iMode = -2;
            }

            if (iMode <= 0)
            {
                Scierror(999, _("%s: Wrong value for input argument #%d: Scalar positive integer expected.\n"), "size", 2);
                iMode = -2;
            }
        }
    }
    else
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: string or scalar expected.\n"), "size", 2);
        iMode = -2;
    }

    return iMode;
}
