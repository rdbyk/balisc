/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Antoine ELIAS
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

#include <string.h>
#include "funcmanager.hxx"
#include "context.hxx"
#include "functions_gw.hxx"
#include "string.hxx"

extern "C"
{
#include "localization.h"
#include "Scierror.h"
}

using types::Double;
using types::Function;
using types::InternalType;
using types::String;
using types::typed_list;
using symbol::Symbol;
using symbol::Context;

static const char fname[] = "funclist";

Function::ReturnValue sci_funclist(typed_list &in, int _iRetCount, typed_list &out)
{
    Context* pContext = Context::getInstance();

    if (in.size() > 1)
    {
        Scierror(77, _("%s: Wrong number of input arguments: %d to %d expected.\n"), fname, 0, 1);
        return Function::Error;
    }

    std::wstring pstLibName;

    if (in.size() == 1)
    {
        InternalType* pIT = in[0];

        if (pIT->isString() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), fname, 1);
            return Function::Error;
        }

        String *pS = pIT->getAs<String>();

        if (pS->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: A single string expected.\n"), fname, 1);
            return Function::Error;
        }

        pstLibName = pS->getFirst();
    }
    else
    {
        pstLibName.clear();
    }

    std::list<Symbol> funcList;
    int size = pContext->getFunctionList(funcList, pstLibName);

    if (size)
    {
        String *pS = new String(size, 1);
        std::list<Symbol>::iterator it;

        int i = 0;
        for (auto it : funcList)
        {
            pS->set(i++, 0, it.getName().c_str());
        }

        out.push_back(pS);
    }
    else
    {
        out.push_back(Double::Empty());
    }

    return Function::OK;
}
