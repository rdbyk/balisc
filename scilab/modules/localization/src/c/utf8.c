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

// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

#define UTF8_ACCEPT 0
#define UTF8_REJECT 1

static const uint8_t utf8d[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 00..1f
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 20..3f
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 40..5f
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 60..7f
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9, // 80..9f
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, // a0..bf
  8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, // c0..df
  0xa,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x4,0x3,0x3, // e0..ef
  0xb,0x6,0x6,0x6,0x5,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8, // f0..ff
  0x0,0x1,0x2,0x3,0x5,0x8,0x7,0x1,0x1,0x1,0x4,0x6,0x1,0x1,0x1,0x1, // s0..s0
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1, // s1..s2
  1,2,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1, // s3..s4
  1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,1,1,1,1,1,1, // s5..s6
  1,3,1,1,1,1,1,3,1,3,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // s7..s8
};

static inline uint32_t decode(uint32_t* state, uint32_t* codep, uint32_t byte)
{
  uint32_t type = utf8d[byte];

  *codep = (*state != UTF8_ACCEPT) ?
    (byte & 0x3fu) | (*codep << 6) :
    (0xff >> type) & (byte);

  *state = utf8d[256 + *state*16 + type];
  return *state;
}

size_t wchar_length_from_utf8(const char* utf8)
{
    uint32_t codepoint;
    uint32_t state = 0;
    
    size_t count = 0;
    char* s = (char*)utf8;
    for ( ; *s; ++s)
    {
        if (!decode(&state, &codepoint, (uint32_t)(*s)))
        {
            count += 1;
        }
    }
    
    if (state == UTF8_ACCEPT)
    {
        return count;
    }
    else
    {
        return -1; /* non-valid utf8 */
    }
}
