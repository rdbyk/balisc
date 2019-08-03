/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2014 - Scilab Enterprises - Cedric DELAMARRE
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "cacsd_gw.hxx"
#include "function.hxx"
#include "double.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "elem_common.h"

    extern void C2F(ssxmc)( int*, int*, double*, int*, double*, int*, int*, int*, double*,
                            double*, double*, double*, double*, double*, int*);

    extern void C2F(polmc)( int*, int*, int*, int*, double*, double*, double*, double*, double*, double*,
                            int*, int*, int*, double*, double*, double*, double*, double*, double*, double*);

}

using types::Double;
using types::Function;
using types::typed_list;

Function::ReturnValue sci_ppol(typed_list &in, int _iRetCount, typed_list &out)
{
    Double* pDblA = NULL;
    Double* pDblB = NULL;
    Double* pDblP = NULL;

    double dblEps = 0.1 * sqrt(nc_eps_machine());

    int iOne   = 1;
    int iSizeP = 0;
    int iColB  = 0;

    bool isDeletable = false;

    if (in.size() != 3)
    {
        Scierror(71, 3);
        return Function::Error;
    }

    // get poles
    if (in[2]->isDouble() == false)
    {
        Scierror(95, 3);
        return Function::Error;
    }

    pDblP = in[2]->getAs<Double>();
    iSizeP = pDblP->getSize();

    // get matrix B
    if (in[1]->isDouble() == false)
    {
        Scierror(94, 2);
        return Function::Error;
    }

    pDblB = in[1]->getAs<Double>();

    if (pDblB->isComplex())
    {
        Scierror(94, 2);
        return Function::Error;
    }

    iColB = pDblB->getCols();

    // get matrix A
    if (in[0]->isDouble() == false)
    {
        Scierror(94, 1);
        return Function::Error;
    }

    pDblA = in[0]->getAs<Double>();

    if (pDblA->isComplex())
    {
        Scierror(94, 1);
        return Function::Error;
    }

    if (pDblA->getRows() != pDblA->getCols())
    {
        Scierror(103, 1);
        return Function::Error;
    }

    if (pDblA->getRows() != iSizeP || pDblB->getRows() != iSizeP)
    {
        Scierror(100, 2, _("compatible dimensions"));
        return Function::Error;
    }

    if (iSizeP == 0)
    {
        out.push_back(Double::Empty());
        return Function::OK;
    }

    pDblA = pDblA->clone()->getAs<Double>();
    pDblB = pDblA->clone()->getAs<Double>();
    pDblP = pDblA->clone()->getAs<Double>();

    Double* pDblOut = new Double(iColB, iSizeP);

    double* pdblG = pDblOut->get();
    double* pdblZ = new double[iSizeP * iSizeP];
    int iSizeWork = std::max(iSizeP * iColB + 3 * iColB,
        iColB * iColB + iColB * std::max(2, iColB) + 3 * iColB + 2 * iSizeP);
    double* pdblW = new double[iSizeWork];
    int* piW = new int[iSizeP];

    pDblP->setComplex(true);
    double* pdblPReal = pDblP->get();
    double* pdblPImg  = pDblP->getImg();

    int idc = 0;
    int inc = 0;

    // calcul de la forme canonique orthogonale
    C2F(ssxmc)(&iSizeP, &iColB, pDblA->get(), &iSizeP, pDblB->get(), &idc, &inc, piW, pdblZ,
               pdblW + iColB, pdblW + iColB + iSizeP * iColB, pdblW + 2 * iColB + iSizeP * iColB,
               pdblW, &dblEps, &iOne);

    if (idc < iSizeP)
    {
        Scierror(200);
        delete[] pdblZ;
        delete[] pdblW;
        delete[] piW;
        delete pDblP;
        delete pDblB;
        delete pDblA;
        pDblOut->killMe();
        return Function::Error;
    }

    double* pdblW1 = pdblW  + iColB + iColB * iColB;
    double* pdblW2 = pdblW1 + iColB * std::max(2, iColB);
    double* pdblW3 = pdblW2 + iSizeP;
    double* pdblW4 = pdblW3 + iSizeP;
    double* pdblW5 = pdblW4 + iColB;

    // placement of poles
    int iErr = 0;
    C2F(polmc)( &iSizeP, &iColB, &iSizeP, &iColB, pDblA->get(), pDblB->get(), pdblG, pdblPReal, pdblPImg,
                pdblZ, &inc, piW, &iErr, pdblW, pdblW + iColB, pdblW1, pdblW2, pdblW3, pdblW4, pdblW5);

    delete[] pdblZ;
    delete[] pdblW;
    delete[] piW;
    delete pDblP;
    delete pDblB;
    delete pDblA;

    if (iErr)
    {
        Scierror(200);
        pDblOut->killMe();
        return Function::Error;
    }

    out.push_back(pDblOut);
    return Function::OK;
}
