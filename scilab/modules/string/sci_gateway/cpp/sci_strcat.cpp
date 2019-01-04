/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Allan CORNET , Cong WU
 * Copyright (C) DIGITEO - 2010 - Allan CORNET
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

#include "string_gw.hxx"
#include "function.hxx"
#include "string.hxx"
#include "double.hxx"

extern "C"
{
#include <string.h>
#include <stdio.h>
#include "sci_malloc.h"
#include "Scierror.h"
#include "localization.h"
}

types::Function::ReturnValue sci_strcat(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int iMode               = 0;
    wchar_t* pwstToInsert   = NULL;

    if (in.size() < 1 || in.size() > 3)
    {
        Scierror(71, 1, 3);
        return types::Function::Error;
    }

    for (int i = 1 ; i < in.size() ; i++)
    {
        if (in[i]->isString() == false)
        {
            Scierror(90, i + 1, _("matrix of strings"));
            return types::Function::Error;
        }
    }

    if (in[0]->isDouble() && in[0]->getAs<types::Double>()->isEmpty())
    {
        out.push_back(types::Double::Empty());
        return types::Function::OK;
    }
    else if (in[0]->isString() == false)
    {
        Scierror(91, 1);
        return types::Function::Error;
    }

    if (in.size() == 3)
    {
        wchar_t wcMode = in[2]->getAs<types::String>()->getFirst()[0];
        switch (wcMode)
        {
            case L'r' :
                iMode = 1;
                break;
            case L'c' :
                iMode = 2;
                break;
            default :
                Scierror(110, 2, _("'r' or 'c'"));
                return types::Function::Error;
        }
    }

    if (in.size() > 1)
    {
        if (in[1]->getAs<types::String>()->getSize() != 1)
        {
            Scierror(91, 2);
            return types::Function::Error;
        }

        pwstToInsert = in[1]->getAs<types::String>()->getFirst();
    }

    types::String* pS = in[0]->getAs<types::String>();

    types::String* pOut = NULL;
    switch (iMode)
    {
        case 0 : //"*"
        {
            pOut = new types::String(1, 1);

            int iLen = 1;
            for (int i = 0; i < pS->getSize(); i++)
            {
                iLen += (int)wcslen(pS->get(i));
            }

            if (pwstToInsert != NULL)
            {
                iLen += (int)wcslen(pwstToInsert) * (pS->getSize() - 1);
            }

            wchar_t* pwstOut = (wchar_t*)MALLOC(sizeof(wchar_t) * iLen);

            wchar_t* dst = pwstOut;
            wchar_t* src = pS->getFirst();
            while (*src != L'\0')
            {
                *dst++ = *src++;
            }
            if (pwstToInsert)
            {
                for (int i = 1; i < pS->getSize(); i++)
                {
                    wchar_t* src = pwstToInsert;
                    while (*src != L'\0')
                    {
                        *dst++ = *src++;
                    }
                    src = pS->get(i);
                    while (*src != L'\0')
                    {
                        *dst++ = *src++;
                    }
                }
            }
            else
            {
                for (int i = 1; i < pS->getSize(); i++)
                {
                    wchar_t* src = pS->get(i);
                    while (*src != L'\0')
                    {
                        *dst++ = *src++;
                    }
                    
                }
            }
            *dst = L'\0';

            pOut->set(0, pwstOut);
            FREE(pwstOut);
        }
        break;
        case 1 : //"r"
        {
            pOut = new types::String(1, pS->getCols());

            for (int i = 0 ; i < pS->getCols() ; i++)
            {
                int iLen = 1;
                for (int j = 0 ; j < pS->getRows() ; j++)
                {
                    iLen += (int)wcslen(pS->get(j, i));
                }

                if (pwstToInsert != NULL)
                {
                    iLen += (int)wcslen(pwstToInsert) * (pS->getRows() - 1);
                }

                wchar_t* pwstOut = (wchar_t*)MALLOC(sizeof(wchar_t) * iLen);

                wchar_t* dst = pwstOut;
                wchar_t* src = pS->get(0, i);
                while (*src != L'\0')
                {
                    *dst++ = *src++;
                }
                if (pwstToInsert)
                {
                    for (int j = 1; j < pS->getRows(); j++)
                    {
                        wchar_t* src = pwstToInsert;
                        while (*src != L'\0')
                        {
                            *dst++ = *src++;
                        }
                        src = pS->get(j, i);
                        while (*src != L'\0')
                        {
                            *dst++ = *src++;
                        }
                    }
                }
                else
                {
                    for (int j = 1; j < pS->getRows(); j++)
                    {
                        wchar_t* src = pS->get(j, i);
                        while (*src != L'\0')
                        {
                            *dst++ = *src++;
                        }
                        
                    }
                }
                *dst = L'\0';
                
                pOut->set(i, pwstOut);
                FREE(pwstOut);
            }
            break;
        }
        case 2 : //"c"
        {
            pOut = new types::String(pS->getRows(), 1);

            for (int i = 0; i < pS->getRows(); i++)
            {
                int iLen = 1;
                for (int j = 0 ; j < pS->getCols() ; j++)
                {
                    iLen += (int)wcslen(pS->get(i, j));
                }

                if (pwstToInsert != NULL)
                {
                    iLen += (int)wcslen(pwstToInsert) * (pS->getCols() - 1);
                }

                wchar_t* pwstOut = (wchar_t*)MALLOC(sizeof(wchar_t) * iLen);

                wchar_t* dst = pwstOut;
                wchar_t* src = pS->get(i, 0);
                while (*src != L'\0')
                {
                    *dst++ = *src++;
                }
                if (pwstToInsert)
                {
                    for (int j = 1; j < pS->getCols(); j++)
                    {
                        wchar_t* src = pwstToInsert;
                        while (*src != L'\0')
                        {
                            *dst++ = *src++;
                        }
                        src = pS->get(i, j);
                        while (*src != L'\0')
                        {
                            *dst++ = *src++;
                        }
                        
                    }
                }
                else
                {
                    for (int j = 1; j < pS->getCols(); j++)
                    {
                        wchar_t* src = pS->get(i, j);
                        while (*src != L'\0')
                        {
                            *dst++ = *src++;
                        }
                        
                    }
                }
                *dst = L'\0';
                
                pOut->set(i, pwstOut);
                FREE(pwstOut);
            }
            break;
        }
    }

    out.push_back(pOut);
    return types::Function::OK;
}
