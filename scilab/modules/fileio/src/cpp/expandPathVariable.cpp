/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
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

#include <wchar.h>
#include "context.hxx"
#include "string.hxx"
#include "filesep.h"
#include "expandPathVariable.h"

extern "C"
{
#include "charEncoding.h"
#include "sci_malloc.h"
#include "PATH_MAX.h"
#include "api_scilab.h"
#include "getlongpathname.h"
#include "os_string.h"
}

/*--------------------------------------------------------------------------*/
struct VARIABLEALIAS
{
    const wchar_t *Alias;
    const wchar_t *VariableName;
    size_t AliasLength;
    symbol::Variable* var;
};
/*--------------------------------------------------------------------------*/
#define ALIASLENGTH(x) (sizeof(x) / sizeof(wchar_t) - 1)
#ifdef _MSC_VER
#define NB_ALIAS 7
#else
#define NB_ALIAS 6
#endif
static struct VARIABLEALIAS VARIABLES_words[NB_ALIAS] =
{
    {L"SCIHOME", L"SCIHOME", ALIASLENGTH(L"SCIHOME"), NULL},
#ifdef _MSC_VER
    {L"WSCI", L"WSCI", ALIASLENGTH(L"WSCI"), NULL},
#endif
    {L"SCI", L"SCI", ALIASLENGTH(L"SCI"), NULL},
    {L"~", L"home", ALIASLENGTH(L"~"), NULL},
    {L"HOME", L"home", ALIASLENGTH(L"HOME"), NULL},
    {L"home", L"home", ALIASLENGTH(L"home"), NULL},
    {L"TMPDIR", L"TMPDIR", ALIASLENGTH(L"TMPDIR"), NULL}
};
/*--------------------------------------------------------------------------*/
static wchar_t *getVariableValueDefinedInScilab(VARIABLEALIAS* var);
/*--------------------------------------------------------------------------*/
wchar_t *expandPathVariableW(const wchar_t *wcstr)
{
    wchar_t *wcexpanded = NULL;
    if (wcstr)
    {
        int i = 0;
        int lenStr = (int)wcslen(wcstr);

        for (i = 0; i < NB_ALIAS; i++)
        {
            int lenAlias = 0;

            /* input is ALIAS without subdirectory */
            if (wcscmp(VARIABLES_words[i].Alias, wcstr) == 0)
            {
                wchar_t *wcexpanded = getVariableValueDefinedInScilab(&VARIABLES_words[i]);
                if (wcexpanded)
                {
                    FileSep::Normalize(wcexpanded);
                    return wcexpanded;
                }
            }

            lenAlias = (int)VARIABLES_words[i].AliasLength;

            if (lenStr > lenAlias)
            {
                wchar_t *wcBegin = (wchar_t *)MALLOC(sizeof(wchar_t) * (lenAlias + 1));
                if (wcBegin)
                {
                    wcsncpy(wcBegin, wcstr, lenAlias);
                    wcBegin[lenAlias] = '\0';

                    if (wcscmp(wcBegin, VARIABLES_words[i].Alias) == 0 )
                    {
                        if ( (wcstr[lenAlias] == L'/') || (wcstr[lenAlias] == L'\\') )
                        {
                            wchar_t * newBegin = getVariableValueDefinedInScilab(&VARIABLES_words[i]);
                            if (newBegin)
                            {
                                int lengthnewBegin = (int)wcslen(newBegin);
                                wcexpanded = (wchar_t *)MALLOC(sizeof(wchar_t) * (lengthnewBegin + (lenStr - lenAlias + 1)));
                                if (wcexpanded)
                                {
                                    wcscat(wcpcpy(wcexpanded, newBegin), &wcstr[lenAlias]);
                                    FREE(wcBegin);
                                    wcBegin = NULL;
                                    free(newBegin);
                                    newBegin = NULL;
                                    FileSep::Normalize(wcexpanded);
                                    return wcexpanded;
                                }
                                FREE(newBegin);
                                newBegin = NULL;
                            }
                        }
                    }
                    FREE(wcBegin);
                    wcBegin = NULL;
                }
            }
        }

        /* Variables not founded returns a copy of input */
        wcexpanded = os_wcsdup(wcstr);
        FileSep::Normalize(wcexpanded);
        return wcexpanded;
    }
    return wcexpanded;
}
/*--------------------------------------------------------------------------*/
char *expandPathVariable(const char* str)
{
    char *expanded = NULL;
    wchar_t *wstr = to_wide_string(str);

    if (wstr)
    {
        wchar_t *wcexpanded = expandPathVariableW(wstr);
        if (wcexpanded)
        {
            expanded = wide_string_to_UTF8(wcexpanded);
            FREE(wcexpanded);
            wcexpanded = NULL;
        }
        FREE(wstr);
        wstr = NULL;
    }
    return expanded;
}
/*--------------------------------------------------------------------------*/
wchar_t *getVariableValueDefinedInScilab(VARIABLEALIAS* _var)
{
    if (_var)
    {
        if (_var->var == NULL)
        {
            _var->var = symbol::Context::getInstance()->getOrCreate(symbol::Symbol(_var->VariableName));
        }

        types::InternalType *pIT = _var->var->get();
        if (pIT == NULL || pIT->isString() == false)
        {
            return NULL;
        }

        BOOL bConvLong = FALSE;
        types::String* pS = pIT->getAs<types::String>();
        return getlongpathnameW( pS->getFirst(), &bConvLong);
    }
    return NULL;
}
/*--------------------------------------------------------------------------*/
void resetVariableValueDefinedInScilab(void)
{
    for (int i = 0; i < NB_ALIAS; i++)
    {
        VARIABLES_words[i].var = NULL;
    }
}
/*--------------------------------------------------------------------------*/
