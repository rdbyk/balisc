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
 
#ifndef __FILESEP_H__
#define __FILESEP_H__

#define FILESEP_UNIX_CHAR '/'
#define FILESEP_WIN64_CHAR '\\'

#define FILESEP_UNIX_WCHAR L'/'
#define FILESEP_WIN64_WCHAR L'\\'

#if defined (__linux__) || defined(__APPLE__)
#define FILESEP_NORM_CHAR FILESEP_UNIX_CHAR
#define FILESEP_NORM_WCHAR FILESEP_UNIX_WCHAR
#define FILESEP_ALT_CHAR FILESEP_WIN64_CHAR
#define FILESEP_ALT_WCHAR FILESEP_WIN64_WCHAR
#elif defined(_WIN64)
#define FILESEP_NORM_CHAR FILESEP_WIN64_CHAR
#define FILESEP_NORM_WCHAR FILESEP_WIN64_WCHAR
#define FILESEP_ALT_CHAR FILESEP_UNIX_CHAR
#define FILESEP_ALT_WCHAR FILESEP_UNIX_WCHAR
#endif

#define FILESEP_IS_CHAR(x) ((x) == FILESEP_UNIX_CHAR || (x) == FILESEP_WIN64_CHAR)
#define FILESEP_IS_WCHAR(x) ((x) == FILESEP_UNIX_WCHAR || (x) == FILESEP_WIN64_WCHAR)

#ifdef __cplusplus
class FileSep
{
public:
    static void Normalize(char* s);
    static void Normalize(wchar_t* w);
    static void Unix(char* s);
    static void Win64(char* s);
    static void Unix(wchar_t* w);
    static void Win64(wchar_t* w);
};
#endif

#ifdef __cplusplus
extern "C"
{
#endif
void FileSep_Normalize(char* s);
void FileSep_Normalize_W(wchar_t* w);
void FileSep_Unix(char* s);
void FileSep_Win64(char* s);
void FileSep_Unix_W(wchar_t* w);
void FileSep_Win64_W(wchar_t* w);
#ifdef __cplusplus
}
#endif

#endif
