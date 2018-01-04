/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Allan CORNET
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
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
/*--------------------------------------------------------------------------*/
#include "funcmanager.hxx"
#include "filemanager.hxx"
#include "fileio_gw.hxx"
#include "function.hxx"
#include "string.hxx"

extern "C"
{
#include "Scierror.h"
#include "splitpath.h"
#include "localization.h"
}

/*--------------------------------------------------------------------------*/
types::Function::ReturnValue sci_fileext(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(999, _("%s: Wrong number of input arguments: %d expected.\n"), "fileext" , 1);
        return types::Function::Error;
    }

    if (_iRetCount != 1)
    {
        Scierror(78, _("%s: Wrong number of output argument(s): %d expected.\n"), "fileext", 1);
        return types::Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: Matrix of strings expected.\n"), "fileext", 1);
        return types::Function::Error;
    }

    types::String* pS = in[0]->getAs<types::String>();
    types::String* pOut = new types::String(pS->getRows(), pS->getCols());

    for (int i = 0 ; i < pS->getSize() ; i++)
    {
        wchar_t* pwstIn = pS->get(i);
        size_t size_pwstIn = wcslen(pwstIn) + 1;

        wchar_t* pwstExtension = new wchar_t[size_pwstIn];

        splitpathW(pwstIn, FALSE, NULL, NULL, NULL, pwstExtension);
        pOut->set(i, pwstExtension);

        delete[] pwstExtension;
    }

    out.push_back(pOut);
    return types::Function::OK;
}
/*--------------------------------------------------------------------------*/

