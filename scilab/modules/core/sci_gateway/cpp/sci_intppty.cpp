/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2014 - Scilab Enterprises - Antoine ELIAS
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

#include "core_gw.hxx"
#include "double.hxx"
#include "string.hxx"
#include "function.hxx"
#include <list>
#include "configvariable.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "os_string.h"
}

static const char fname[] = "intppty";

types::Function::ReturnValue sci_intppty(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    bool bAdd = true;
    if (in.size() > 2)
    {
        Scierror(72, 0, 2);
        return types::Function::Error;
    }

    if (in.size() == 2)
    {
        if (in[1]->isString() == false || in[1]->getAs<types::String>()->isScalar() == false)
        {
            Scierror(102, 2);
            return types::Function::Error;
        }

        types::String* pMode = in[1]->getAs<types::String>();
        if (os_wcsicmp(pMode->getFirst(), L"add") == 0)
        {
            bAdd = true;
        }
        else if (os_wcsicmp(pMode->getFirst(), L"remove") == 0)
        {
            bAdd = false;
        }
        else
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: '%s' or '%s' expected.\n"), fname, 2, "add", "remove");
            return types::Function::Error;
        }

    }

    if (in.size() > 0)
    {
        if (in[0]->isString() == false || in[0]->getAs<types::String>()->isScalar() == false)
        {
            Scierror(102, 1);
            return types::Function::Error;
        }


        types::String* pS = in[0]->getAs<types::String>();

        if (bAdd)
        {
            ConfigVariable::addReferenceModule(pS->getFirst());
        }
        else
        {
            ConfigVariable::removeReferenceModule(pS->getFirst());
        }
    }
    else
    {
        //get list of reference modules
        std::list<std::wstring> l = ConfigVariable::getReferenceModules();
        if (l.size() == 0)
        {
            out.push_back(types::Double::Empty());
        }
        else
        {
            types::String* pOut = new types::String(1, (int)l.size());
            std::list<std::wstring>::iterator it = l.begin();

            for (int i = 0; it != l.end() ; ++it, ++i)
            {
                pOut->set(i, (*it).c_str());
            }

            out.push_back(pOut);
        }
    }
    return types::Function::OK;
}
