/* Balisc (https: *github.com/rdbyk/balisc/)
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

#ifndef __BALISC_STRCMP_H__
#define __BALISC_STRCMP_H__

#if defined(__SSE4_2__)

int sse42_strcmp(const char* s1, const char* s2);
#define balisc_strcmp sse42_strcmp

int balisc_strcmp(const char* s1, const char* s2);

#else

#include <string.h>
#define balisc_strcmp strcmp
    
#endif

#endif /* __BALISC_STRCMP_H__ */
