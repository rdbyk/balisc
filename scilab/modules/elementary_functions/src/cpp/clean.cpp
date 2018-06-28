/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2014 - Scilab Enterprises - Cedric Delamarre
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyrigth (C) 2017 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
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
#include <algorithm>
#include "clean.hxx"

extern "C"
{
#include "elem_common.h"
}

void clean(double* pdblReal, double* pdblImg, int iSize, double dEpsA, double dEpsR)
{
    if (pdblImg)
    {
        double dNorm = 0;
        for (int i = 0 ; i < iSize ; i++)
        {
            double d = std::abs(pdblReal[i]) + std::abs(pdblImg[i]);
            if (std::isfinite(d))
            {
               dNorm += d;
            }
        }

        double dEps = std::max(dEpsA, dEpsR * dNorm);
        for (int i = 0 ; i < iSize ; i++)
        {
            if (std::abs(pdblImg[i]) <= dEps)
            {
                pdblImg[i] = 0;
            }

            if (std::abs(pdblReal[i]) <= dEps)
            {
                pdblReal[i] = 0;
            }
        }
    }
    else
    {
        double dNorm = 0;
        for (int i = 0 ; i < iSize ; i++)
        {
            double d = std::abs(pdblReal[i]);
            if (std::isfinite(d))
            {
               dNorm += d;
            }
        }
        double dEps = std::max(dEpsA, dEpsR * dNorm);
        for (int i = 0 ; i < iSize ; i++)
        {
            if (std::abs(pdblReal[i]) <= dEps)
            {
                pdblReal[i] = 0;
            }
        }
    }
}
