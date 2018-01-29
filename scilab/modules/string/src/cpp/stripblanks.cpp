// Balisc (https://github.com/rdbyk/balisc/)
//
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
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

#include "stripblanks.hxx"

extern "C"
{
#include "sci_malloc.h"
#include "os_string.h"
}

using types::String;

String * stripblanks(String *InputStrings, bool bRemoveTAB, int flag)
{
    bool bRemoveLeading = flag == -1 || flag == 0;
    bool bRemoveTrailing = flag == 1 || flag == 0;

    String *pOutputStrings = new String(InputStrings->getDims(), InputStrings->getDimsArray());

    if (pOutputStrings)
    {
        for (int i = 0; i < InputStrings->getSize(); ++i)
        {
            wchar_t* pwstUnStripped = os_wcsdup(InputStrings->get(i));
            wchar_t* pwstStripped = pwstUnStripped;

            if (bRemoveTAB)
            {
                if (bRemoveLeading)
                {
                    while(iswspace((wint_t)*pwstStripped))
                    {
                        ++pwstStripped;
                    }

                    if(*pwstStripped == L'\0')
                    {
                        pOutputStrings->set(i, pwstStripped);
                        FREE(pwstUnStripped);
                        continue;
                    }
                }

                if (bRemoveTrailing)
                {
                    wchar_t* pwstStrippedEnd = pwstStripped + wcslen(pwstStripped) - 1;

                    while(pwstStrippedEnd > pwstStripped && iswspace((wint_t)*pwstStrippedEnd))
                    {
                        --pwstStrippedEnd;
                    }

                    *(pwstStrippedEnd + 1) = L'\0';
                }
            }
            else
            {
                if (bRemoveLeading)
                {
                    while(*pwstStripped == L' ')
                    {
                        ++pwstStripped;
                    }

                    if(*pwstStripped == L'\0')
                    {
                        pOutputStrings->set(i, pwstStripped);
                        FREE(pwstUnStripped);
                        continue;
                    }
                }

                if (bRemoveTrailing)
                {
                    wchar_t* pwstStrippedEnd = pwstStripped + wcslen(pwstStripped) - 1;

                    while(pwstStrippedEnd > pwstStripped && *pwstStrippedEnd == L' ')
                    {
                        --pwstStrippedEnd;
                    }

                    *(pwstStrippedEnd + 1) = L'\0';
                }
            }

            pOutputStrings->set(i, pwstStripped);
            FREE(pwstUnStripped);
        }
    }

    return pOutputStrings;
}
