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

#include <cwchar>
#include "filesep.h"

void FileSep::Normalize(char* s)
{
    char* t = s;

    while (*t)
    {
        if (*t == FILESEP_ALT_CHAR)
        {
            *t = FILESEP_NORM_CHAR;
        }
        ++t;
    }
}

void FileSep::Normalize(wchar_t* w)
{
    wchar_t* t = w;

    while (*t)
    {
        if (*t == FILESEP_ALT_WCHAR)
        {
            *t = FILESEP_NORM_WCHAR;
        }
        ++t;
    }
}

void FileSep::Unix(char* s)
{
    char* t = s;

    while (*t)
    {
        if (*t == FILESEP_WIN64_CHAR)
        {
            *t = FILESEP_UNIX_CHAR;
        }
        ++t;
    }
}

void FileSep::Win64(char* s)
{
    char* t = s;

    while (*t)
    {
        if (*t == FILESEP_UNIX_CHAR)
        {
            *t = FILESEP_WIN64_CHAR;
        }
        ++t;
    }
}

void FileSep::Unix(wchar_t* w)
{
    wchar_t* t = w;

    while (*t)
    {
        if (*t == FILESEP_WIN64_WCHAR)
        {
            *t = FILESEP_UNIX_WCHAR;
        }
        ++t;
    }
}

void FileSep::Win64(wchar_t* w)
{
    wchar_t* t = w;

    while (*t)
    {
        if (*t == FILESEP_UNIX_WCHAR)
        {
            *t = FILESEP_WIN64_WCHAR;
        }
        ++t;
    }
}

void FileSep_Normalize(char* s)
{
    FileSep::Normalize(s);
}

void FileSep_Normalize_W(wchar_t* w)
{
    FileSep::Normalize(w);
}

void FileSep_Unix(char* s)
{
    FileSep::Unix(s);
}

void FileSep_Win64(char* s)
{
    FileSep::Win64(s);
}

void FileSep_Unix_W(wchar_t* w)
{
    FileSep::Unix(w);
}

void FileSep_Win64_W(wchar_t* w)
{
    FileSep::Win64(w);
}
