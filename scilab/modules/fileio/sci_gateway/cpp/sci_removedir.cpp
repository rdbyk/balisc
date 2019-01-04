/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2011 - Digiteo - Cedric DELAMARRE
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

#include "fileio_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "bool.hxx"
#include "configvariable.hxx"

extern "C"
{
#include <string.h>
#include "sci_malloc.h"
#include "removedir.h"
#include "isdir.h"
#include "expandPathVariable.h"
#include "sciprint.h"
#include "Scierror.h"
#include "localization.h"
#include "PATH_MAX.h"
}

static const char fname[] = "removedir";

types::Function::ReturnValue sci_removedir(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71, 1);
        return types::Function::Error;
    }

    if (in[0]->isString() == false || in[0]->getAs<types::String>()->getSize() != 1)
    {
        Scierror(91, 1);
        return types::Function::Error;
    }

    wchar_t* pwstPath = expandPathVariableW(in[0]->getAs<types::String>()->getFirst());
    int iRet = 0;
    if (!isdirW(pwstPath))
    {
        if (ConfigVariable::getWarningMode())
        {
            sciprint(_("%s: Warning: Directory '%ls' does not exist.\n"), fname, pwstPath);
        }
    }
    else
    {
        iRet = removedirW(pwstPath);
    }

    FREE(pwstPath);
    types::Bool* pOut = new types::Bool(iRet);

    out.push_back(pOut);
    return types::Function::OK;
}
