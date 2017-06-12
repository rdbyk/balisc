/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2012 - DIGITEO - Cedric DELAMARRE
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyrigth (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 * 
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */
/*--------------------------------------------------------------------------*/

#include "elem_func_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "overload.hxx"
#include "configvariable.hxx"

extern "C"
{
#include "Scierror.h"
#include "sciprint.h"
#include "localization.h"
#include "elem_common.h"
}

#include <complex>
#include <cmath>

/*
clear a;nb = 2500;a = rand(nb, nb);tic();log(a);toc
clear a;nb = 2500;a = -rand(nb, nb);tic();log(a);toc
clear a;nb = 2500;a = rand(nb, nb); a = a + a *%i;tic();log(a);toc
*/

/*--------------------------------------------------------------------------*/
types::Function::ReturnValue sci_log(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int iAlert = 1;
    int ieee = ConfigVariable::getIeee();
    
    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d to %d expected.\n"), "log", 1);
        return types::Function::Error;
    }

    if (_iRetCount > 1)
    {
        Scierror(78, _("%s: Wrong number of output argument(s): %d expected.\n"), "log", 1);
        return types::Function::Error;
    }

    if (in[0]->isDouble() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_log";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    types::Double* pDblIn = in[0]->getAs<types::Double>();
    types::Double* pDblOut = new types::Double(pDblIn->getDims(), pDblIn->getDimsArray(), pDblIn->isComplex());

    double* pInR = pDblIn->get();
    double* pOutR = pDblOut->get();
    int size = pDblIn->getSize();
    if (pDblIn->isComplex())
    {
        double* pInI = pDblIn->getImg();
        double* pOutI = pDblOut->getImg();
        
        double InR, InI;
                
        for (int i = 0; i < size; i++)
        {
            InR = pInR[i];
            InI = pInI[i];
            
            if (ieee != 2 && iAlert)
            {
                if (InR == 0 && InI == 0)
                {
                    if (ieee == 0)
                    {
                        Scierror(999, _("%s: Wrong value for input argument #%d : Singularity of the function.\n"), "log", 1);
                        return types::Function::Error;
                    }
                    else if (ieee == 1)
                    {
                        if (ConfigVariable::getWarningMode())
                        {
                            sciprint(_("%ls: Warning: Wrong value for input argument #%d : Singularity of the function.\n"), "log", 1);
                        }
                    }

                    iAlert = 0;
                }
            }
            
            std::complex<double> lz(std::log(std::complex<double>(InR, InI)));
            pOutR[i] = lz.real();
            pOutI[i] = lz.imag();
        }
    }
    else
    {
        bool bIsLessZero = false;
        
        double InR;
        for (int i = 0; i < size; i++)
        {
            InR = pInR[i];
            
            if (InR < 0)
            {
                bIsLessZero = true;
            }
            else if (iAlert && ieee != 2)
            {
                if (InR == 0)
                {
                    if (ieee == 0)
                    {
                        Scierror(999, _("%s: Wrong value for input argument #%d : Singularity of the function.\n"), "log", 1);
                        return types::Function::Error;
                    }
                    else if (ieee == 1)
                    {
                        if (ConfigVariable::getWarningMode())
                        {
                            sciprint(_("%ls: Warning: Wrong value for input argument #%d : Singularity of the function.\n"), "log", 1);
                        }
                    }
                    
                    iAlert = 0;
                }
            }
        }

        if (bIsLessZero)
        {
            pDblOut->setComplex(true);
            double* pOutI = pDblOut->getImg();

            double xr_i;
            for (int i = 0; i < size; i++)
            {
                xr_i = pInR[i];
                if (xr_i >= 0)
                {
                    pOutR[i] = std::log(xr_i);
                    pOutI[i] = 0.0;
                }
                else
                {
                     pOutR[i] = std::log(-xr_i);
                     pOutI[i] = M_PI;
                }
                //std::complex<double> lz(std::log(std::complex<double>(pInR[i], 0.0)));
                //pOutR[i] = lz.real();
                //pOutI[i] = lz.imag();
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                pOutR[i] = std::log(pInR[i]);
            }
        }
    }

    out.push_back(pDblOut);
    return types::Function::OK;
}
/*--------------------------------------------------------------------------*/
