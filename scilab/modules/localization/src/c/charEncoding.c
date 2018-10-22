/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - Yung-Jang Lee
 * Copyright (C) 2009 - DIGITEO - Antoine ELIAS , Allan CORNET
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
#ifndef _MSC_VER
#include <iconv.h>
#include <errno.h>
#endif

#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "charEncoding.h"
#include "sci_malloc.h"
#include "utf8.h"
#include "strlen.h"
/*--------------------------------------------------------------------------*/
#ifdef _MSC_VER
#include <Windows.h>

char *wide_string_to_UTF8(const wchar_t *_wide)
{
    char *buf = NULL;
    DWORD size = 0;
    DWORD dwFlags = 0;

    if ((wchar_t *)NULL == _wide)
    {
        return (char *)NULL;
    }
    size = WideCharToMultiByte(CP_UTF8, dwFlags, _wide, -1, NULL, 0, NULL, 0);
    if (size == 0)
    {
        return (char *)NULL;
    }
    buf = (char*)MALLOC(sizeof(char) * size);
    if (buf)
    {
        WideCharToMultiByte(CP_UTF8, dwFlags, _wide, -1, buf, size, NULL, 0);
        if (size <= 0)
        {
            FREE(buf);
            return (char *)NULL;
        }
    }

    buf[size - 1] = '\0';
    return buf;
}
/*--------------------------------------------------------------------------*/
wchar_t *to_wide_string(const char *_UTFStr)
{
    int nwide = 0;
    wchar_t *_buf = NULL;
    UINT codePage = CP_UTF8;

    if (_UTFStr == NULL)
    {
        return NULL;
    }

    nwide = MultiByteToWideChar(codePage, MB_ERR_INVALID_CHARS, _UTFStr, -1, NULL, 0);
    if (nwide == 0)
    {
        if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
        {
            codePage = CP_ACP;
            nwide = MultiByteToWideChar(codePage, 0, _UTFStr, -1, NULL, 0);
        }

        if (nwide == 0)
        {
            return NULL;
        }
    }

    _buf = (wchar_t *)MALLOC(nwide * sizeof(wchar_t));
    if (_buf == NULL)
    {
        return NULL;
    }

    if (MultiByteToWideChar(codePage, 0, _UTFStr, -1, _buf, nwide) == 0)
    {
        FREE(_buf);
        _buf = NULL;
    }

    _buf[nwide - 1] = L'\0';
    return _buf;
}
/*--------------------------------------------------------------------------*/
int wcstat(char* filename, struct _stat *st)
{
    int stat_result = 0;
    wchar_t *wfilename = to_wide_string(filename);
    stat_result = _wstat(wfilename, st);
    FREE(wfilename);
    return stat_result;
}
/*--------------------------------------------------------------------------*/
#else // Linux or Mac OS X
/*--------------------------------------------------------------------------*/

static iconv_t __WCHAR_T_from_UTF_8 = NULL;

char *wide_string_to_UTF8(const wchar_t *_wide)
{
    size_t len_utf8;
    char* utf8;
    
    if (_wide == NULL)
    {
        return NULL;
    }

    if ((len_utf8 = utf8_length_from_wchar(_wide)) < 0)
    {
        return NULL;
    }

    utf8 = (char*)MALLOC((len_utf8 + 1)*sizeof(char));
    
    /* FIXME: malloc was successful? */
    
    if (utf8_from_wchar(_wide, utf8) == 0)
    {
        return utf8;
    }
    else
    {
        return NULL;
    }
}
/*--------------------------------------------------------------------------*/
wchar_t *to_wide_string(const char *_UTFStr)
{
    wchar_t* pOutSave = NULL;
    char* pInSave = NULL;
    size_t iSize = 0;
    size_t iLeftIn = 0;
    size_t iLeftOut = 0;
    wchar_t* pOut = NULL;

    if (_UTFStr == NULL)
    {
        return NULL;
    }

    /* cd_UTF8_to_UTF16 = iconv_open("WCHAR_T", "UTF-8"); */
    if (__WCHAR_T_from_UTF_8 == NULL)
    {
        __WCHAR_T_from_UTF_8 = iconv_open("WCHAR_T", "UTF-8");
    }

    iLeftIn = balisc_strlen(_UTFStr);
    pInSave = (char*)_UTFStr;

    iLeftOut = (iLeftIn + 1) * sizeof(wchar_t);
    
//    pOut = (wchar_t*)MALLOC(iLeftOut);
//    memset(pOut, 0x00, iLeftOut);
    pOut = (wchar_t*)CALLOC(iLeftIn + 1, sizeof(wchar_t));
    
    pOutSave = pOut;

    iSize = iconv(__WCHAR_T_from_UTF_8, (char**)&_UTFStr, &iLeftIn, (char**)&pOut, &iLeftOut);
//    iSize = wchar_from_utf8(_UTFStr, pOut);

    if (iSize == (size_t)(-1))
    {
        _UTFStr = pInSave;
        pOut = pOutSave;
        memset(pOut, 0x00, iLeftOut);
        
//        iSize = iconv(__WCHAR_T_from_ISO_8859_1, (char**)&_UTFStr, &iLeftIn, (char**)&pOut, &iLeftOut);
        iSize = wchar_from_iso8859_1(_UTFStr, pOut);
        
        if (iSize == (size_t)(-1))
        {
            FREE(pOut);
            return NULL;
        }
    }
    return pOutSave;
}
/*--------------------------------------------------------------------------*/
int wcstat(char* filename, struct stat *st)
{
    return stat(filename, st);
}
/*--------------------------------------------------------------------------*/
#endif
/*--------------------------------------------------------------------------*/
static int ReadUTF8Character(const char* str, int *nBytes)
{
    const unsigned char* s = (const unsigned char*)(str);
    unsigned char c = s[0];

    if (c < 0x80)
    {
        *nBytes = 1;
        return c;
    }
    else if (c < 0xC2)
    {
        return -1;
    }
    else if (c < 0xE0)
    {
        if (s[1] == 0 || (s[1] ^ 0x80) >= 0x40)
        {
            return -1;
        }
        *nBytes = 2;
        return ((s[0] & 0x1F) << 6) + (s[1] ^ 0x80);
    }
    else if (c < 0xF0)
    {
        if (s[1] == 0 || s[2] == 0 || (s[1] ^ 0x80) >= 0x40
                || (s[2] ^ 0x80) >= 0x40 || (c == 0xE0 && s[1] < 0xA0))
        {
            return -1;
        }
        *nBytes = 3;
        return ((s[0] & 0xF) << 12) + ((s[1] ^ 0x80) << 6) + (s[2] ^ 0x80);
    }
    else if (c < 0xF5)
    {
        if (s[1] == 0 || s[2] == 0 || s[3] == 0 || (s[1] ^ 0x80) >= 0x40
                || (s[2] ^ 0x80) >= 0x40 || (s[3] ^ 0x80) >= 0x40
                || (c == 0xF0 && s[1] < 0x90) || (c == 0xF4 && s[1] > 0x8F))
        {
            return -1;
        }
        *nBytes = 4;
        return ((s[0] & 0x07) << 18) + ((s[1] ^ 0x80) << 12) + ((s[2] ^ 0x80) << 6)
               + (s[3] ^ 0x80);
    }
    else
    {
        return -1;
    }
}
/*--------------------------------------------------------------------------*/
BOOL IsValidUTF8(const char*  pStText)
{
    const char* s =  pStText;
    while (*s != 0)
    {
        int nBytes = 0;
        if (ReadUTF8Character(s, &nBytes) < 0)
        {
            return FALSE;
        }
        s += nBytes;
    }

    return TRUE;
}
/*--------------------------------------------------------------------------*/
