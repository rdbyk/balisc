/* Balisc (https://github.com/rdbyk/balisc/)
 *
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
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

#ifndef __ERRMSGS_H
#define __ERRMSGS_H

#ifdef __cplusplus
#include <map>
extern std::map<int, const char*> ErrorMessages;
extern "C" {
#endif

char* ErrorMessageByNumber(int n);

#ifdef __cplusplus
}
#endif

#endif /* _ERRMSGS_H */
