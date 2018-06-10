/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Allan CORNET
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include "strsubst.h"
#include "sci_malloc.h"
#include "pcre_private.h"
#include "os_string.h"
#include "charEncoding.h"
#include "pcre_error.h"
#include "strlen.h"
/*-------------------------------------------------------------------------------------*/
char *strsub(const char* input_string, const char* string_to_search, const char* replacement_string)
{
    const char *occurrence_str = NULL;
    char* result_str = NULL;
    char *replacedString = NULL;
    int count = 0, len = 0;

    if (input_string == NULL)
    {
        return NULL;
    }

    if (string_to_search == NULL || replacement_string == NULL)
    {
        return os_strdup(input_string);
    }

    occurrence_str = strstr (input_string, string_to_search);
    if (occurrence_str == NULL)
    {
        return os_strdup(input_string);
    }

    if (balisc_strlen(replacement_string) > balisc_strlen(string_to_search))
    {
        count = 0;
        len = (int)balisc_strlen(string_to_search);
        if (len)
        {
            occurrence_str = input_string;
            while (occurrence_str != NULL && *occurrence_str != '\0')
            {
                occurrence_str = strstr (occurrence_str, string_to_search);
                if (occurrence_str != NULL)
                {
                    occurrence_str += len;
                    count++;
                }
            }
        }
        len = count * ((int)balisc_strlen(replacement_string) - 
                       (int)balisc_strlen(string_to_search)) + 
                       (int)balisc_strlen(input_string);
    }
    else
    {
        len = (int)balisc_strlen(input_string);
    }

    replacedString = (char*)MALLOC (sizeof(char) * (len + 1));
    if (replacedString == NULL)
    {
        return NULL;
    }

    occurrence_str = input_string;
    result_str = replacedString;
    len = (int)balisc_strlen(string_to_search);
    while (*occurrence_str != '\0')
    {
        if (*occurrence_str == string_to_search[0] && strncmp (occurrence_str, string_to_search, len) == 0)
        {
            const char *N = NULL;
            N = replacement_string;
            while (*N != '\0')
            {
                *result_str++ = *N++;
            }
            occurrence_str += len;
        }
        else
        {
            *result_str++ = *occurrence_str++;
        }
    }
    *result_str = '\0';

    return replacedString;
}
/*-------------------------------------------------------------------------------------*/
wchar_t *wcssub_reg(const wchar_t* _pwstInput, const wchar_t* _pwstSearch, const wchar_t* _pwstReplace, int* _piErr)
{
    pcre_error_code iPcreStatus = PCRE_FINISHED_OK;
    int iStart = 0;
    int iEnd = 0;
    int len = 0;
    int* arriStart = NULL;
    int* arriEnd = NULL;
    int iOccurs = 0;
    int iJump = 0;

    wchar_t* result = NULL;

    if (_pwstInput == NULL)
    {
        return NULL;
    }

    len = (int)wcslen(_pwstInput);
    arriStart = (int*)MALLOC(sizeof(int) * len);
    arriEnd = (int*)MALLOC(sizeof(int) * len);

    if (_pwstSearch == NULL || _pwstReplace == NULL)
    {
        FREE(arriStart);
        FREE(arriEnd);
        return os_wcsdup(_pwstInput);
    }

    do
    {
        iPcreStatus = wide_pcre_private(_pwstInput + iJump, _pwstSearch, &iStart, &iEnd, NULL, NULL);
        if (iPcreStatus == PCRE_FINISHED_OK)
        {
            if (iEnd != iStart)
            {
                arriStart[iOccurs] = iStart + iJump;
                arriEnd[iOccurs++] = iEnd + iJump;
                iJump += iEnd;
            }
            else if (iEnd == 0 && _pwstInput[iJump] != L'\0')
            {
                //avoid infinite loop
                iJump++;
            }
        }
        else if (iPcreStatus != NO_MATCH)
        {
            pcre_error("strsubst", iPcreStatus);
            FREE(arriStart);
            FREE(arriEnd);
            return NULL;
        }
    }
    while (iPcreStatus == PCRE_FINISHED_OK && iStart != iEnd);

    if (iOccurs)
    {
        int i = 0;
        int replaceLen = (int)wcslen(_pwstReplace);
        int finalSize = len;

        //compute final size
        for (i = 0; i < iOccurs; ++i)
        {
            finalSize -= (arriEnd[i] - arriStart[i]);
            finalSize += replaceLen;
        }

        result = (wchar_t*)MALLOC(sizeof(wchar_t) * (finalSize + 1));
        result[0] = '\0';

        //from start to first occurence
        wcsncat(result, _pwstInput, arriStart[0]);
        result[arriStart[0]] = '\0';

        for (i = 0; i < iOccurs - 1; ++i)
        {
            int curLen = (int)wcslen(result);
            int partLen = arriStart[i + 1] - arriEnd[i];
            //insert replace string
            wcscat(result, _pwstReplace);
            //copy part between 2 occurences
            wcsncat(result, _pwstInput + arriEnd[i], partLen);
            result[curLen + replaceLen + partLen] = '\0';
        }

        wcscat(result, _pwstReplace);
        //copy part after last occurence
        wcscat(result, _pwstInput + arriEnd[iOccurs - 1]);
    }
    else
    {
        *_piErr = iPcreStatus;
        result = os_wcsdup(_pwstInput);
    }

    FREE(arriStart);
    FREE(arriEnd);

    return result;
}
/*-------------------------------------------------------------------------------------*/
wchar_t **wcssubst_reg(const wchar_t** _pwstInput, int _iInputSize, const wchar_t* _pwstSearch, const wchar_t* _pwstReplace, int* _piErr)
{
    wchar_t** pwstOutput = NULL;

    if (_pwstInput != NULL && _pwstSearch != NULL && _pwstReplace != NULL)
    {
        int i = 0;
        pwstOutput = (wchar_t**)MALLOC(sizeof(wchar_t*) * _iInputSize);
        for (i = 0 ; i < _iInputSize ; i++)
        {
            const wchar_t* pwst = _pwstInput[i];
            pwstOutput[i] = wcssub_reg(pwst, _pwstSearch, _pwstReplace, _piErr);
        }
    }
    return pwstOutput;
}
/*-------------------------------------------------------------------------------------*/
wchar_t **wcssubst(const wchar_t** _pwstInput, int _iInputSize, const wchar_t* _pwstSearch, const wchar_t* _pwstReplace)
{
    wchar_t** pwstOutput = NULL;

    if (_pwstInput != NULL && _pwstSearch != NULL && _pwstReplace != NULL)
    {
        int i = 0;
        pwstOutput = (wchar_t**)MALLOC(sizeof(wchar_t*) * _iInputSize);
        for (i = 0 ; i < _iInputSize ; i++)
        {
            const wchar_t* pwst = _pwstInput[i];
            if (pwst[0] == L'\0')
            {
                pwstOutput[i] = os_wcsdup(L"");
            }
            else
            {
                pwstOutput[i] = wcssub(pwst, _pwstSearch, _pwstReplace);
            }
        }
    }
    return pwstOutput;
}
/*-------------------------------------------------------------------------------------*/
wchar_t *wcssub(const wchar_t* _pwstInput, const wchar_t* _pwstSearch, const wchar_t* _pwstReplace)
{
    int i               = 0;
    int iOccurs         = 0;
    size_t iReplace     = 0;
    size_t iSearch      = 0;
    size_t iOffset      = 0;

    size_t* piStart     = NULL;

    const wchar_t* pwstPos  = NULL;
    wchar_t* pwstOutput     = NULL;

    if (_pwstInput == NULL)
    {
        return NULL;
    }

    if (_pwstInput[0] == L'\0')
    {
        return os_wcsdup(L"");
    }

    if (_pwstSearch == NULL || _pwstReplace == NULL)
    {
        return os_wcsdup(_pwstInput);
    }

    iSearch     = wcslen(_pwstSearch);
    iReplace    = wcslen(_pwstReplace);
    piStart     = (size_t*)MALLOC(sizeof(size_t) * wcslen(_pwstInput));
    pwstPos     = _pwstInput;

    while (pwstPos)
    {
        pwstPos = wcsstr(pwstPos, _pwstSearch);
        if (pwstPos)
        {
            piStart[iOccurs++]  = pwstPos - _pwstInput;
            iOffset             += iReplace - iSearch;
            pwstPos++;
        }
    }

    pwstOutput = (wchar_t*)CALLOC(wcslen(_pwstInput) + iOffset + 1, sizeof(wchar_t));

    if (iOccurs == 0)
    {
        wcscpy(pwstOutput, _pwstInput);
    }
    else
    {
        wchar_t* pwstTemp = wcpncpy(pwstOutput, _pwstInput, piStart[0]);
        pwstTemp = wcpcpy(pwstTemp, _pwstReplace);

        for (i = 1 ; i < iOccurs ; i++)
        {
            pwstTemp = wcpncpy(pwstTemp, _pwstInput + piStart[i - 1] + iSearch, piStart[i] - (iSearch + piStart[i - 1]));
            pwstTemp = wcpcpy(pwstTemp, _pwstReplace);
        }

        wcpcpy(pwstTemp, _pwstInput + piStart[iOccurs - 1] + iSearch);
    }

    FREE(piStart);
    return pwstOutput;
}
/*-------------------------------------------------------------------------------------*/
