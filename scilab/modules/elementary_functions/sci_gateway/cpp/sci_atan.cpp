/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
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

#include <complex>
#include <cmath>
#include "elem_func_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "overload.hxx"
#include "configvariable.hxx"
#include "atan.hxx"

extern "C"
{
#include "Scierror.h"
#include "sciprint.h"
#include "localization.h"
}

static const char fname[] = "atan";

types::Function::ReturnValue sci_atan(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::Double* pDblX   = NULL;
    types::Double* pDblY   = NULL;
    types::Double* pDblOut = NULL;

    if (in.size() < 1 || in.size() > 2)
    {
        Scierror(72, fname, 1, 2);
        return types::Function::Error;
    }

    if (in[0]->isDouble() == false)
    {
        std::wstring wstFuncName = L"%" + in[0]->getShortTypeStr() + L"_atan";
        return Overload::call(wstFuncName, in, _iRetCount, out);
    }

    pDblX = in[0]->getAs<types::Double>();

    if (in.size() == 1)
    {
        if (pDblX->isComplex())
        {
            if (balisc::atan_singularity(pDblX))
            {
                if (ConfigVariable::getIeee() == 0)
                {
                    Scierror(999, _("%s: Wrong value for input argument #%d : Singularity of the function.\n"), fname, 1);
                    return types::Function::Error;
                }
                else if (ConfigVariable::getIeee() == 1 && ConfigVariable::getWarningMode())
                {
                    sciprint(_("%s: Warning: Wrong value for input argument #%d : Singularity of the function.\n"), fname, 1);
                }
            }
            
            out.push_back(balisc::atan_complex(pDblX));
            return types::Function::OK;
        }
        else
        {
            out.push_back(balisc::atan_real(pDblX));
            return types::Function::OK;
        }
    }
    else // in.size() == 2
    {
        pDblY = in[1]->getAs<types::Double>();

        if (pDblX->isComplex() || pDblY->isComplex())
        {
            Scierror(94, 2);
            return types::Function::Error;
        }

        if (pDblX->getSize() != pDblY->getSize())
        {
            Scierror(999, _("%s: Wrong size for input argument #%d and #%d: Same size expected.\n"), fname, 1, 2);
            return types::Function::Error;
        }
        
        out.push_back(balisc::atan2(pDblX, pDblY));
        return types::Function::OK;
    }
}
