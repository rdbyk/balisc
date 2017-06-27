/* Balisc (https://github.com/rdbyk/balisc/)
 * 
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
 * 02110-1301, USA.
 */
 
#include "utf8.h"
#include <stdint.h>
 
size_t utf8_length_from_wchar(const wchar_t* ucs4)
{
    size_t len_utf8 = 0;
    wchar_t* s = (wchar_t*)ucs4;
    
    while (*s != L'\0')
    {
        if (*s <= 0x0000007F)
        {
            len_utf8++;
        }
        else if (*s <= 0x000007FF)
        {
            len_utf8 += 2;
        }
        else if (*s <= 0x0000FFFF)
        {
            len_utf8 += 3;
        }
        else if (*s <= 0x0010FFFF)
        {
            len_utf8 += 4;
        }
        else
        {
            /* violation of RFC 3629 */
            len_utf8 = -1;
            break;
        }
        s++;
    }
    
    return len_utf8;
}


int utf8_from_wchar(const wchar_t* ucs4, char* utf8)
{
    char* d = utf8;
    wchar_t* s = (wchar_t*)ucs4;

    while(*s != L'\0')
    {
        if (*s <= 0x0000007F)
        {
            *d = (char)*s;
        }
        else if (*s <= 0x000007FF)
        {
            *d = 0xc0 | (*s >> 6);
            d++;
		    *d = 0x80 | (*s & 0x3f);
        }
        else if (*s <= 0x0000FFFF)
        {
            *d = 0xe0 | (*s >> 12);
            d++;
            *d = 0x80 | ((*s >> 6) & 0x3f);
            d++;
            *d = 0x80 | (*s & 0x3f);
        }
        else if (*s <= 0x0010FFFF)
        {
            *d = 0xf0 | (*s >> 18);
            d++;
            *d = 0x80 | ((*s >> 12) & 0x3f);
            d++;
		    *d = 0x80 | ((*s >> 6) & 0x3f);
            d++;
            *d= 0x80 | (*s & 0x3f);
        }
        else
        {
            /* violation of RFC 3629 */
            return 1; /* failure */
        }
        d++;
        s++;
    }
    *d = '\0';
    
    return 0; /* success */
}

size_t wchar_from_utf8(const char *utf8, wchar_t* ucs4)
{
    /* size_t n = 0; */
    wchar_t* d = ucs4;
    
    char* s = (char*)utf8;
    while (*s)
    {
        if (*s < 0x80) /* 0xxxxxxx */
        {
            *d = *s;
            d++;
            s++;
            /* n++; */
        }
        else if ((s[0] & 0xe0) == 0xc0)
        {
            /* 110XXXXx 10xxxxxx */
            if ((s[1] & 0xc0) != 0x80 ||
                (s[0] & 0xfe) == 0xc0)                          /* overlong? */
            {
                return -1;
            }
            else
            {
                *d = ((0x1f & s[0]) << 6) | (0x3f & s[1]);
                d++;
                s += 2;
                /* n += 2; */
            }
        } 
        else if ((s[0] & 0xf0) == 0xe0)
        {
            /* 1110XXXX 10Xxxxxx 10xxxxxx */
            if ((s[1] & 0xc0) != 0x80 ||
                (s[2] & 0xc0) != 0x80 ||
                (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) ||      /* overlong? */
                (s[0] == 0xed && (s[1] & 0xe0) == 0xa0) ||  /* surrogate? */
                (s[0] == 0xef && s[1] == 0xbf &&
                (s[2] & 0xfe) == 0xbe))                         /* U+FFFE or U+FFFF? */
            {
                return -1;
            }
            else
            {
                *d = ((0x0f & s[0]) << 12) | ((0x3f & s[1]) << 6) | (0x3f & s[2]);
                d++;
                s += 3;
                /* n += 3; */
            }
        } 
        else if ((s[0] & 0xf8) == 0xf0)
        {
          /* 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx */
            if ((s[1] & 0xc0) != 0x80 ||
                (s[2] & 0xc0) != 0x80 ||
                (s[3] & 0xc0) != 0x80 ||
                (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) ||   /* overlong? */
                (s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4)       /* > U+10FFFF? */
            {
                return -1;
            }
            else
            {
                *d = ((0x07 & s[0]) << 18) | ((0x3f & s[1]) << 12) | ((0x3f & s[2]) << 6) | (0x3f & s[3]);
                d++;
                s += 4;
                /* n += 4; */
            }
        }
        else
        {
            return -1;
        }
    }
    *d = L'\0';
    
    return 0;
}

size_t wchar_from_iso8859_1(const char* iso, wchar_t* ucs4)
{
    size_t len = 0;
    wchar_t* d = ucs4;
    char* s = (char*)iso;
    
    *d = L'\0';
    while ((*s != '\0') && (*s < 0xFF))
    {
        *d = (wchar_t)*s;
        d++;
        s++;
        len++;
    }
    *d = L'\0';
    
    if (*s != '\0')
    {
        return -1;
    }
    else
    {
        return len;
    }
}
