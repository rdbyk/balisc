/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Cong WU , Allan CORNET
 * Copyright (C) DIGITEO - 2009 - Allan CORNET
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

#include "funcmanager.hxx"
#include "string_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "double.hxx"

extern "C"
{
#include "strsubst.h"
#include "localization.h"
#include "Scierror.h"
#include "pcre_error.h"
#include "pcre_private.h"
#include "freeArrayOfPtrs.h"
}

using types::Double;
using types::Function;
using types::String;
using types::typed_list;

static char fname[] = "strsubst";

#define WCHAR_R L'r'
#define WCHAR_S L's'

Function::ReturnValue sci_strsubst(typed_list &in, int _iRetCount, typed_list &out)
{
    bool bRegExp = false;
    if (in.size() < 3 || in.size() > 4)
    {
        Scierror(72, 3, 4);
        return Function::Error;
    }

    if (in.size() > 3)
    {
        if (in[3]->isString() == false && in[3]->getAs<String>()->getSize() != 1)
        {
            Scierror(91, 4);
        }

        if (in[3]->getAs<String>()->getFirst()[0] == WCHAR_R)
        {
            bRegExp = true;
        }
        else if (in[3]->getAs<String>()->getFirst()[0] == WCHAR_S)
        {
            bRegExp = false;
        }
        else
        {
            Scierror(110, 4, _("'s' or 'r'"));
            return Function::Error;
        }
    }

    if (in[2]->isString() == false || in[2]->getAs<String>()->getSize() != 1)
    {
        Scierror(91, 3);
        return Function::Error;
    }

    wchar_t* pwstReplace = in[2]->getAs<String>()->get()[0];

    if (in[1]->isString() == false || in[1]->getAs<String>()->getSize() != 1)
    {
        Scierror(91, 2);
        return Function::Error;
    }

    wchar_t* pwstSearch = in[1]->getAs<String>()->get()[0];

    if (in[0]->isDouble() && in[0]->getAs<Double>()->isEmpty())
    {
        out.push_back(Double::Empty());
        return Function::OK;
    }

    if (in[0]->isString() == false)
    {
        Scierror(90, 1, _("matrix of strings"));
        return Function::Error;
    }

    if (in[1]->getAs<String>()->getFirst()[0] == L'\0')
    {
        // replace nothing
        out.push_back(in[0]);
        return Function::OK;
    }

    String* pS = in[0]->getAs<String>();

    String* pOut = new String(pS->getRows(), pS->getCols());
    wchar_t** pwstOutput = NULL;

    if (bRegExp)
    {
        int iErr = 0;
        pwstOutput = wcssubst_reg(const_cast<const wchar_t**>(pS->get()), pS->getSize(), pwstSearch, pwstReplace, &iErr);
        if (iErr != NO_MATCH && iErr != PCRE_FINISHED_OK && iErr != PCRE_EXIT)
        {
            freeArrayOfPtrs((void**)pwstOutput, pOut->getSize());
            pcre_error(fname, iErr);
            delete pOut;
            return Function::Error;
        }
    }
    else
    {
        pwstOutput = wcssubst(const_cast<const wchar_t**>(pS->get()), pS->getSize(), pwstSearch, pwstReplace);
    }

    pOut->set(pwstOutput);
    freeArrayOfPtrs((void**)pwstOutput, pOut->getSize());
    out.push_back(pOut);
    return Function::OK;
}
