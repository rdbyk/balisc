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

#include "log10.hxx"

#include <complex>
#include <cmath>

/*
clear a;nb = 2500;a = rand(nb, nb);tic();log10(a);toc
clear a;nb = 2500;a = -rand(nb, nb);tic();log10(a);toc
clear a;nb = 2500;a = rand(nb, nb); a = a + a *%i;tic();log10(a);toc
*/

/*--------------------------------------------------------------------------*/
types::Function::ReturnValue sci_log10(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int ieee = ConfigVariable::getIeee();
    
    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), "log10", 1);
        return types::Function::Error;
    }

    if (_iRetCount > 1)
    {
        Scierror(78, _("%s: Wrong number of output argument(s): %d expected.\n"), "log10", 1);
        return types::Function::Error;
    }

    if (in[0]->isDouble() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_log10";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    types::Double* pDblIn = in[0]->getAs<types::Double>();
    
    if (ieee != 2)
    {
        double* pInR = pDblIn->get();
        int size = pDblIn->getSize();
    
        if (pDblIn->isComplex())
        {
            double* pInI = pDblIn->getImg();
        
            for (int i = 0; i < size; i++)
            {
                if (pInR[i] == 0 && pInI[i] == 0)
                {
                    if (ieee == 0)
                    {
                        Scierror(999, _("%s: Wrong value for input argument #%d : Singularity of the function.\n"), "log10", 1);
                        return types::Function::Error;
                    }
                    else // ieee == 1
                    {
                        if (ConfigVariable::getWarningMode())
                        {
                            sciprint(_("%s: Warning: Wrong value for input argument #%d : Singularity of the function.\n"), "log10", 1);
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                if (pInR[i] == 0)
                {
                    if (ieee == 0)
                    {
                        Scierror(999, _("%s: Wrong value for input argument #%d : Singularity of the function.\n"), "log10", 1);
                        return types::Function::Error;
                    }
                    else // ieee == 1
                    {
                        if (ConfigVariable::getWarningMode())
                        {
                            sciprint(_("%s: Warning: Wrong value for input argument #%d : Singularity of the function.\n"), "log10", 1);
                        }
                    }
                    break;
                }
            }
        }
    }
    
    out.push_back(balisc::log10(pDblIn));
    return types::Function::OK;
}
/*--------------------------------------------------------------------------*/
