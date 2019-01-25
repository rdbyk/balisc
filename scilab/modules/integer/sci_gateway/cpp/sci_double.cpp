/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA
 * Copyright (C) 2010 - DIGITEO - ELIAS Antoine
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "integer_gw.hxx"
#include "function.hxx"
#include "int.hxx"
#include "double.hxx"
#include "bool.hxx"

extern "C"
{
#include <stdio.h>
#include "Scierror.h"
#include "localization.h"
}

types::Callable::ReturnValue sci_double(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71, 1);
        return types::Function::Error;
    }

    types::Double* pOut = NULL;
    if (in[0]->isDouble())
    {
        out.push_back(in[0]);
        return types::Function::OK;
    }
    else if (in[0]->isInt() == false && in[0]->isBool() == false)
    {
        Scierror(90, 1, _("integer, boolean, real, or complex"));
        return types::Function::Error;
    }

    types::InternalType::ScilabType type = in[0]->getType();

    switch (type)
    {
        case types::InternalType::ScilabBool :
        {
            types::Bool* pInt = in[0]->getAs<types::Bool>();
            pOut = new types::Double(pInt->getDims(), pInt->getDimsArray());
            double* pd = pOut->get();
            for (int i = 0 ; i < pInt->getSize() ; i++)
            {
                pd[i] = (double)pInt->get(i);
            }
            break;
        }

        case types::InternalType::ScilabInt8 :
        {
            types::Int8* pInt = in[0]->getAs<types::Int8>();
            pOut = new types::Double(pInt->getDims(), pInt->getDimsArray());
            double* pd = pOut->get();
            for (int i = 0 ; i < pInt->getSize() ; i++)
            {
                pd[i] = (double)pInt->get(i);
            }
            break;
        }

        case types::InternalType::ScilabUInt8 :
        {
            types::UInt8* pInt = in[0]->getAs<types::UInt8>();
            pOut = new types::Double(pInt->getDims(), pInt->getDimsArray());
            double* pd = pOut->get();
            for (int i = 0 ; i < pInt->getSize() ; i++)
            {
                pd[i] = (double)pInt->get(i);
            }
            break;
        }

        case types::InternalType::ScilabInt16 :
        {
            types::Int16* pInt = in[0]->getAs<types::Int16>();
            pOut = new types::Double(pInt->getDims(), pInt->getDimsArray());
            double* pd = pOut->get();
            for (int i = 0 ; i < pInt->getSize() ; i++)
            {
                pd[i] = (double)pInt->get(i);
            }
            break;
        }

        case types::InternalType::ScilabUInt16 :
        {
            types::UInt16* pInt = in[0]->getAs<types::UInt16>();
            pOut = new types::Double(pInt->getDims(), pInt->getDimsArray());
            double* pd = pOut->get();
            for (int i = 0 ; i < pInt->getSize() ; i++)
            {
                pd[i] = (double)pInt->get(i);
            }
            break;
        }

        case types::InternalType::ScilabInt32 :
        {
            types::Int32* pInt = in[0]->getAs<types::Int32>();
            pOut = new types::Double(pInt->getDims(), pInt->getDimsArray());
            double* pd = pOut->get();
            for (int i = 0 ; i < pInt->getSize() ; i++)
            {
                pd[i] = (double)pInt->get(i);
            }
            break;
        }

        case types::InternalType::ScilabUInt32 :
        {
            types::UInt32* pInt = in[0]->getAs<types::UInt32>();
            pOut = new types::Double(pInt->getDims(), pInt->getDimsArray());
            double* pd = pOut->get();
            for (int i = 0 ; i < pInt->getSize() ; i++)
            {
                pd[i] = (double)pInt->get(i);
            }
            break;
        }

        case types::InternalType::ScilabInt64 :
        {
            types::Int64* pInt = in[0]->getAs<types::Int64>();
            pOut = new types::Double(pInt->getDims(), pInt->getDimsArray());
            double* pd = pOut->get();
            for (int i = 0 ; i < pInt->getSize() ; i++)
            {
                pd[i] = (double)pInt->get(i);
            }
            break;
        }

        case types::InternalType::ScilabUInt64 :
        {
            types::UInt64* pInt = in[0]->getAs<types::UInt64>();
            pOut = new types::Double(pInt->getDims(), pInt->getDimsArray());
            double* pd = pOut->get();
            for (int i = 0 ; i < pInt->getSize() ; i++)
            {
                pd[i] = (double)pInt->get(i);
            }
            break;
        }

        default :
        {
            Scierror(0);
            return types::Function::Error;
        }
    }

    out.push_back(pOut);
    return types::Function::OK;
}
