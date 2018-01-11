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
 
 #ifndef __USEWMEMCMP_H__
 #define __USEWMEMCMP_H__
 
 #if defined(__GNUC__) && (__SIZEOF_INT__ == __SIZEOF_WCHAR_T__)
 #include <wchar.h>
 #define USE_WMEMCMP
 #else
 #undef USE_WMEMCMP
 #endif
 
 #endif /* __USEWMEMCMP_H__ */
 
