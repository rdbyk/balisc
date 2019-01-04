/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2014 - Scilab Enterprises - Anais Aubert
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
#include "overload.hxx"
#include "double.hxx"
#include "string.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "basic_functions.h"
}

static const wchar_t g_pwstConfigInfo[] = {L"info"};
static const wchar_t g_pwstConfigSeed[] = {L"seed"};

static const wchar_t g_pwstTypeUniform[] = {L"uniform"};
static const wchar_t g_pwstTypeNormal[] = {L"normal"};

static int setRandType(wchar_t _wcType);
static double getNextRandValue(int _iRandType, int* _piRandSave, int _iForceInit);

static double durands(int* _iVal);

static const char fname[] = "rand";

types::Function::ReturnValue sci_rand(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::Double* pOut = NULL;
    static int siRandType = 0;
    static int siRandSave = 0;
    static int iForceInit	= 0;

    int iSizeIn = (int)in.size();
    if (iSizeIn == 0 || iSizeIn == -1)
    {
        //rand or rand()
        double dblRand = getNextRandValue(siRandType, &siRandSave, 0);
        out.push_back(new types::Double(dblRand));
        return types::Function::OK;
    }

    if (in[0]->isString())
    {
        //rand("xxx")
        types::String* pS = in[0]->getAs<types::String>();
        if (pS->getSize() != 1)
        {
            Scierror(102, 1);
            return types::Function::Error;
        }

        wchar_t* pwstKey = pS->getFirst();

        if (pwstKey[0] == g_pwstConfigInfo[0])
        {
            //info
            if (iSizeIn > 1)
            {
                Scierror(71, 1);
                return types::Function::Error;
            }

            if (siRandType == 0)
            {
                out.push_back(new types::String(g_pwstTypeUniform));
            }
            else
            {
                out.push_back(new types::String(g_pwstTypeNormal));
            }
        }
        else if (pwstKey[0] == g_pwstConfigSeed[0])
        {
            //seed
            if (iSizeIn == 1)
            {
                //get
                out.push_back(new types::Double(siRandSave));
            }
            else if (iSizeIn == 2)
            {
                if (in[1]->isDouble() == false || in[1]->getAs<types::Double>()->isScalar() == false)
                {
                    Scierror(101, 2);
                    return types::Function::Error;
                }

                siRandSave = (int)std::max(in[1]->getAs<types::Double>()->getFirst(), double(0));
                iForceInit = 1;
            }
            else
            {
                Scierror(71, 2);
                return types::Function::Error;
            }
        }
        else
        {
            siRandType = setRandType(pwstKey[0]);
        }
    }
    else
    {
        int iRandSave = siRandType;
        if (in[iSizeIn - 1]->isString())
        {
            //uniform ou normal
            types::String* pS = in[iSizeIn - 1]->getAs<types::String>();
            if (pS->getSize() != 1)
            {
                Scierror(102, iSizeIn);
                return types::Function::Error;
            }

            //set randomize law
            iRandSave = siRandType;
            siRandType = setRandType(pS->getFirst()[0]);
            iSizeIn--;
        }

        types::typed_list args;
        std::copy(in.begin(), in.begin() + iSizeIn, back_inserter(args));

        int iDims = 0;
        int* piDims = NULL;
        bool alloc = false;

        bool ret = getDimsFromArguments(args, fname, &iDims, &piDims, &alloc);
        if (ret == false)
        {
            switch (iDims)
            {
                case -1:
                    Scierror(2);
                    break;
                case 1:
                {
                    //call overload
                    return Overload::generateNameAndCall(L"rat", in, _iRetCount, out);
                }
            }

            return types::Function::Error;
        }

        //special case for complex unique complex argument
        bool complex = false;
        if (in.size() == 1 && in[0]->isGenericType())
        {
            complex = in[0]->getAs<types::GenericType>()->isComplex();
        }

        pOut = new types::Double(iDims, piDims, complex);
        if (alloc)
        {
            delete[] piDims;
        }

        double* pd = pOut->get();
        for (int i = 0; i < pOut->getSize(); i++)
        {
            pd[i] = getNextRandValue(siRandType, &siRandSave, iForceInit);
            iForceInit = 0;
        }

        if (pOut->isComplex())
        {
            double* pImg = pOut->getImg();
            for (int i = 0; i < pOut->getSize(); i++)
            {
                pImg[i] = getNextRandValue(siRandType, &siRandSave, iForceInit);
            }
        }
        out.push_back(pOut);
        //retore previous law
        siRandType = iRandSave;
    }

    return types::Function::OK;
}

static double getNextRandValue(int _iRandType, int* _piRandSave, int _iForceInit)
{
    static int siInit = TRUE;
    static double sdblImg = 0;
    static double sdblR = 0;
    double dblReal = 0;
    double dblVal = 0;
    double dblTemp = 2;

    if (_iForceInit)
    {
        siInit = TRUE;
    }

    if (_iRandType == 0)
    {
        dblVal = durands(_piRandSave);
    }
    else
    {
        if (siInit == TRUE)
        {
            while (dblTemp > 1)
            {
                dblReal = 2 * durands(_piRandSave) - 1;
                sdblImg = 2 * durands(_piRandSave) - 1;
                dblTemp = dblReal * dblReal + sdblImg * sdblImg;
            }
            sdblR = std::sqrt(-2 * std::log(dblTemp) / dblTemp);
            dblVal = dblReal * sdblR;
        }
        else
        {
            dblVal = sdblImg * sdblR;
        }
        siInit = !siInit;
    }
    return dblVal;
}

static int setRandType(wchar_t _wcType)
{
    if (_wcType == L'g' || _wcType == L'n')
    {
        return 1;
    }
    return 0;
}

double durands(int* _iVal)
{
    static int ia = 0, ic = 0, itwo = 2, m2 = 0, m = 0, mic = 0;
    static double halfm = 0, s = 0;

    if (m2 == 0)
    {
        m = 1;
        while (m > m2)
        {
            m2 = m;
            m = itwo * m2;
        }
        halfm = m2;

        ia = 8 * (int)(halfm * atan(1) / 8 + 0.5) + 5;
        ic = 2 * (int)(halfm * (0.5 - sqrt(3) / 6) + 0.5) + 1;
        mic = (m2 - ic) + m2;

        s = 0.5 / halfm;
    }

    *_iVal *= ia;

    if (*_iVal > mic)
    {
        *_iVal = (*_iVal - m2) - m2;
    }

    *_iVal += ic;

    if (*_iVal / 2 > m2)
    {
        *_iVal = (*_iVal - m2) - m2;
    }

    if (*_iVal < 0)
    {
        *_iVal = (*_iVal + m2) + m2;
    }

    return (double) * _iVal * s;
}
