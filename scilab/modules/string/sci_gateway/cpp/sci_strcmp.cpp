/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) Digiteo 2011 - Cedric DELAMARRE
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */


#include "function.hxx"
#include "string.hxx"
#include "list.hxx"
#include "double.hxx"
#include "function.hxx"
#include "string_gw.hxx"

extern "C"
{
#include "core_math.h"
#include "localization.h"
#include "Scierror.h"
#include "BOOL.h"
#include "stringsCompare.h"
}

#define CHAR_I 'i'
#define CHAR_S 's'

types::Function::ReturnValue sci_strcmp(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    types::Double* pOutDouble   = NULL;
    types::String* pString1     = NULL;
    types::String* pString2     = NULL;
    wchar_t* pwcChar3           = NULL;
    BOOL do_stricmp             = FALSE;

    if (in.size() < 2 || in.size() > 3)
    {
        Scierror(72, 2, 3);
        return types::Function::Error;
    }

    if (in[0]->isString() == false)
    {
        Scierror(91, 1);
        return types::Function::Error;
    }

    if (in[1]->isString() == false)
    {
        Scierror(91, 2);
        return types::Function::Error;
    }

    pString1 = in[0]->getAs<types::String>();
    pString2 = in[1]->getAs<types::String>();

    if (pString1->getSize() != pString2->getSize() && pString2->isScalar() == false)
    {
        Scierror(102, 2);
        return types::Function::Error;
    }

    if (in.size() == 3)
    {
        if (in[2]->isString() == false || in[2]->getAs<types::String>()->isScalar() == false || wcslen(in[2]->getAs<types::String>()->getFirst()) != 1)
        {
            Scierror(90, 3, _("character"));
            return types::Function::Error;
        }

        pwcChar3 = in[2]->getAs<types::String>()->getFirst();
        if ( (pwcChar3[0] != CHAR_I) && (pwcChar3[0] != CHAR_S))
        {
            Scierror(110, 3, _("'i' or 's'"));
            return types::Function::Error;
        }

        if (pwcChar3[0] == CHAR_I)
        {
            do_stricmp = TRUE;
        }
    }

    int *values = stringsCompare(pString1->get(), pString1->getSize(), pString2->get(), pString2->getSize(), do_stricmp);

    if (values)
    {
        pOutDouble  = new types::Double(pString1->getDims(), pString1->getDimsArray());
        pOutDouble->setInt(values);
        FREE(values);
    }
    else
    {
        Scierror(1);
    }

    out.push_back(pOutDouble);
    return types::Function::OK;
}
