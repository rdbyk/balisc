/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010 - DIGITEO - Allan CORNET
 * Copyright (C) 2010 - DIGITEO - Antoine ELIAS
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Siddhartha Gairola
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
#include "stripblanks.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "os_string.h"
}

/*--------------------------------------------------------------------------*/
#define BLANK_CHARACTER L' '
#define TAB_CHARACTER L'\t'
/*--------------------------------------------------------------------------*/
static wchar_t* subwcs(const wchar_t *_pstStr, int _iStartPos, int _iEndPos);
/*--------------------------------------------------------------------------*/
types::String * stripblanks(types::String *InputStrings, bool bRemoveTAB, int flag)
{
    types::String *pOutputStrings = InputStrings->clone();
    //flag = -1 to remove leading spaces, flag = 1 to remove trailing spaces, flag = 0 to remove both.
    if (pOutputStrings)
    {
        for (int x = 0; x < InputStrings->getSize(); x++)
        {
            wchar_t* pStr = InputStrings->get(x);
            int iInputStartIndex = 0;
            int iInputLength = static_cast<int>(wcslen(pStr));
            int iInputEndIndex = iInputLength;

            /* search character ' ' or TAB from end of the string */
            if (flag == 1 || flag == 0)
            {
                for (int i = iInputLength - 1; i >= 0; i--)
                {
                    if (pStr[i] == BLANK_CHARACTER || (bRemoveTAB == true && pStr[i] == TAB_CHARACTER))
                    {
                        iInputEndIndex--;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            /* search character ' ' or TAB from beginning of the string */
            if (flag == -1 || flag == 0)
            {
                for (int i = 0; i < iInputLength; i++)
                {
                    if (pStr[i] == BLANK_CHARACTER || (bRemoveTAB == true && pStr[i] == TAB_CHARACTER))
                    {
                        iInputStartIndex++;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            wchar_t* pwstReplace = subwcs(pStr, iInputStartIndex, iInputEndIndex);
            pOutputStrings->set(x, pwstReplace);
            FREE(pwstReplace);
        }
    }

    return pOutputStrings;
}
/*--------------------------------------------------------------------------*/
static wchar_t* subwcs(const wchar_t *_pstStr, int _iStartPos, int _iEndPos)
{
    int iLen = _iEndPos - _iStartPos;
    wchar_t* pwstBuf = NULL;

    //bad len or empty string
    if (iLen < 0 || _pstStr[0] == L'\0')
    {
        return os_wcsdup(L"");
    }

    pwstBuf = (wchar_t*)MALLOC(sizeof(wchar_t) * (iLen + 1)); //+1 for null termination
    if (pwstBuf)
    {
        wcsncpy(pwstBuf, _pstStr + _iStartPos, iLen);   /*Put a part of str into stbuf*/
        pwstBuf[iLen] = L'\0';
    }
    return pwstBuf;
}
/*------------------------------------------------------------------------*/
