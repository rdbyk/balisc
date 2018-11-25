/* C++ code produced by gperf version 3.0.4 */
/* Command-line: gperf -m 50 expandPathVariable.gperf  */
/* Computed positions: -k'1' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 21 "expandPathVariable.gperf"

// Balisc (https://github.com/rdbyk/balisc/)
//
// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301, USA.
//

/* Function "getVariableValueDefinedInScilab" (cf. end of file)
 *
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
#include "getlongpathname.h"
#include "os_string.h"
#include "strlen.h"
}

#define FILESEPS_STR "/\\"
#define FILESEPS_WSTR L"/\\"

struct alias {char *name; wchar_t *true_name; symbol::Variable* variable;};
#line 86 "expandPathVariable.gperf"
struct alias;

#define TOTAL_KEYWORDS 7
#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 7
#define MIN_HASH_VALUE 1
#define MAX_HASH_VALUE 8
/* maximum key range = 8, duplicates = 0 */

class Hash
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static struct alias *lookup_alias (const char *str, unsigned int len);
};

inline unsigned int
Hash::hash (register const char *str, register unsigned int len)
{
  static unsigned char asso_values[] =
    {
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 4, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 0, 0, 9, 9, 1, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 0, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 0, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
      9, 9, 9, 9, 9, 9
    };
  return len + asso_values[(unsigned char)str[0]];
}

static struct alias aliaslist[] =
  {
    {""},
#line 93 "expandPathVariable.gperf"
    {"~", L"home", NULL},
    {""},
#line 89 "expandPathVariable.gperf"
    {"SCI", L"SCI", NULL},
#line 95 "expandPathVariable.gperf"
    {"home", L"home", NULL},
#line 91 "expandPathVariable.gperf"
    {"WSCI", L"WSCI", NULL},
#line 96 "expandPathVariable.gperf"
    {"TMPDIR", L"TMPDIR", NULL},
#line 88 "expandPathVariable.gperf"
    {"SCIHOME", L"SCIHOME", NULL},
#line 94 "expandPathVariable.gperf"
    {"HOME", L"home", NULL}
  };

struct alias *
Hash::lookup_alias (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = aliaslist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &aliaslist[key];
        }
    }
  return 0;
}
#line 97 "expandPathVariable.gperf"

static wchar_t *getVariableValueDefinedInScilab(struct alias* a);

wchar_t *expandPathVariableW(const wchar_t *wcstr)
{
    size_t n = wcscspn(wcstr, FILESEPS_WSTR);

    if (n)
    {
        wchar_t* s = os_wcsdup(wcstr);
        // terminate string at first file separator
        s[n] = L'\0';
        char* e = wide_string_to_UTF8(s);
        struct alias* a = Hash::lookup_alias(e, n);
        FREE(s);
        FREE(e);

        if (a)
        {
            wchar_t* w = getVariableValueDefinedInScilab(a);

            if (w)
            {
                wchar_t* p = (wchar_t*)MALLOC((wcslen(wcstr) + wcslen(w) - n + 1) * sizeof(wchar_t));
                if (p)
                {
                    wcscat(wcpcpy(p, w), &(wcstr[n]));
                    FileSep::Normalize(p);
                }

                FREE(w);

                return p;
            }
        }
    }

    wchar_t* p = os_wcsdup(wcstr);

    if (p)
    {
        FileSep::Normalize(p);
    }

    return p;
}

char *expandPathVariable(const char* str)
{
    if (str)
    {
        size_t n = strcspn(str, FILESEPS_STR);

        if (n)
        {
            char* e = strndup(str, n);
            struct alias* a = Hash::lookup_alias(e, n);
            FREE(e);

            if (a)
            {
                wchar_t* w = getVariableValueDefinedInScilab(a);

                if (w)
                {
                    char* v = wide_string_to_UTF8(w);
                    FREE(w);

                    char* p = (char*)MALLOC((balisc_strlen(str) + balisc_strlen(v) - n + 1) * sizeof(char));
                    if (p)
                    {
                        strcat(stpcpy(p, v), &(str[n]));
                        FileSep::Normalize(p);
                    }

                    FREE(v);

                    return p;
                }
            }
        }

        char* p = os_strdup(str);

        if (p)
        {
            FileSep::Normalize(p);
        }

        return p;
    }
    else
    {
        return NULL;
    }
}

void resetVariableValueDefinedInScilab(void)
{
    for (int i = 0; i <= MAX_HASH_VALUE; ++i)
    {
        if (aliaslist[i].name[0] != '\0')
        {
            aliaslist[i].variable = NULL;
        }
    }
}

/* Function "getVariableValueDefinedInScilab"
 *
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

wchar_t *getVariableValueDefinedInScilab(struct alias* a)
{
    if (a->variable == NULL)
    {
        a->variable = symbol::Context::getInstance()->getOrCreate(symbol::Symbol(a->true_name));
    }

    types::InternalType *pIT = a->variable->get();

    if (pIT == NULL || pIT->isString() == false)
    {
        return NULL;
    }

    BOOL bConvLong = FALSE;
    types::String* pS = pIT->getAs<types::String>();

    return getlongpathnameW(pS->getFirst(), &bConvLong);
}
