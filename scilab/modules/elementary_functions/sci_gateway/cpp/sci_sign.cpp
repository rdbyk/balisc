/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2014 - Scilab Enterprises - Anais AUBERT
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

#include <cmath>
#include <string.h>
#include "elem_func_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "int.hxx"
#include "overload.hxx"

extern "C"
{
#include "Scierror.h"
#include "balisc_elementary.h"
}

types::Function::ReturnValue sci_sign(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int iRows   = 0;
    int iCols   = 0;
    int iType   = 0;
    int* piAddr = NULL;

    double *pdblReal    = NULL;
    double *pdblImg     = NULL;
    double *pdblRealRet = NULL;
    double *pdblImgRet  = NULL;

    if (in.size() != 1)
    {
        Scierror(71, 1);
        return types::Function::Error;
    }

    if (in[0]->isDouble())
    {
        types::Double* pDblIn = in[0]->getAs<types::Double>();
        int dims = pDblIn->getDims();
        int *dimsArray = pDblIn->getDimsArray();
        int size = pDblIn->getSize();

        if (pDblIn->isComplex())
        {
            types::Double* pOut = new types::Double(dims, dimsArray, true);
            double *dOutR   = pOut->getReal();
            double *dOutImg = pOut->getImg() ;
            double *dInR    = pDblIn->getReal();
            double *dInImg  = pDblIn->getImg() ;

            for (int i = 0; i < size; i++)
            {
                double dblTemp = balisc_hypot_d(dInR[i], dInImg[i]);
                if (dblTemp == 0)
                {
                    dOutR[i] = 0;
                    dOutImg[i] = 0;
                }
                else
                {
                    double inv_dblTemp = 1. / dblTemp;
                    dOutR[i] =  dInR[i] * inv_dblTemp;
                    dOutImg[i] = dInImg[i] * inv_dblTemp;
                }
            }

            out.push_back(pOut);
        }
        else
        {
            types::Double* pOut = new types::Double(dims, dimsArray);
            double * dOutR  = pOut->getReal();
            double * dInR   = pDblIn->getReal();

            for (int i = 0; i < size; i++)
            {
/* https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c */
                double val = dInR[i];
                dOutR[i] = (double(0) < val) - (val < double(0));
            }

            out.push_back(pOut);
        }
    }
    else if(in[0]->isInt())
    {
        switch (in[0]->getType())
        {
            case types::InternalType::ScilabInt8 :
                out.push_back(in[0]->getAs<types::Int8>()->sign());
                break;
            case types::InternalType::ScilabUInt8 :
                out.push_back(in[0]->getAs<types::UInt8>()->sign());
                break;
            case types::InternalType::ScilabInt16 :
                out.push_back(in[0]->getAs<types::Int16>()->sign());
                break;
            case types::InternalType::ScilabUInt16 :
                out.push_back(in[0]->getAs<types::UInt16>()->sign());
                break;
            case types::InternalType::ScilabInt32 :
                out.push_back(in[0]->getAs<types::Int32>()->sign());
                break;
            case types::InternalType::ScilabUInt32 :
                out.push_back(in[0]->getAs<types::UInt32>()->sign());
                break;
            case types::InternalType::ScilabInt64 :
                out.push_back(in[0]->getAs<types::Int64>()->sign());
                break;
            case types::InternalType::ScilabUInt64 :
                out.push_back(in[0]->getAs<types::UInt64>()->sign());
                break;
        }
    }
    else
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_sign";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    return types::Function::OK;
}
