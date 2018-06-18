/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Allan CORNET
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
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
#include "fileio_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "bool.hxx"
#include "configvariable.hxx"

extern "C"
{
#include <string.h>
#include "sci_malloc.h"
#include "createdirectory.h"
#include "isdir.h"
#include "expandPathVariable.h"
#include "sciprint.h"
#include "Scierror.h"
#include "localization.h"
#include "PATH_MAX.h"
}
/*--------------------------------------------------------------------------*/
types::Function::ReturnValue sci_createdir(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d expected.\n"), "createdir", 1);
        return types::Function::Error;
    }

    if (in[0]->isString() == false || in[0]->getAs<types::String>()->getSize() != 1)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A String expected.\n"), "createdir", 1);
        return types::Function::Error;
    }

    wchar_t* pwstPath = expandPathVariableW(in[0]->getAs<types::String>()->getFirst());
    int iRet = 0;
    if (!isdirW(pwstPath))
    {
        iRet = createdirectoryW(pwstPath);
    }
    else
    {
        if (ConfigVariable::getWarningMode())
        {
            sciprint(_("%ls: Warning: Directory '%ls' already exists.\n"), L"createdir", pwstPath);
        }
        iRet = 1;
    }

    FREE(pwstPath);
    types::Bool* pOut = new types::Bool(iRet);

    out.push_back(pOut);
    return types::Function::OK;
}
/*--------------------------------------------------------------------------*/
