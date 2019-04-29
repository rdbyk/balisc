/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2014 - Scilab Enterprises - Anais AUBERT
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

#include "sparse_gw.hxx"
#include "function.hxx"
#include "pointer.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "lu.h"
}

types::Function::ReturnValue sci_ludel(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int ierr        = 0;
    int *fmatindex  = NULL;
    const void *pData = NULL;

    if (in.size() != 1 )
    {
        Scierror(71, 1);
        return types::Function::Error;
    }

    if (in[0]->isPointer() == false)
    {
        Scierror(90, 1, _("handle to sparse LU factors"));
        return types::Function::Error;
    }

    types::Pointer *pPointerIn = in[0]->getAs<types::Pointer>();
    pData = pPointerIn->get();
    fmatindex = (int*)pData;

    C2F(ludel1)(fmatindex, &ierr);
    if (ierr != 0)
    {
        Scierror(110, 1, _("valid LU handle"));
        return types::Function::Error;
    }

    return types::Function::OK;
}
