// Balisc (https://github.com/rdbyk/balisc/)
//
// Copyright (C) 2020 - Dirk Reusch, Kybernetik Dr. Reusch
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

#include "core_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "string.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "sci_malloc.h"
}

#include "errmsgs.h"

using types::Double;
using types::Function;
using types::String;
using types::typed_list;

Function::ReturnValue sci_errmsgs(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 0)
    {
        Scierror(71, 0);
        return Function::Error;
    }

    String* msgs = new String(ErrorMessages.size(), 1);
    Double* num = nullptr;

    if (_iRetCount > 1)
    {
        num = new Double(ErrorMessages.size(), 1);
    }
    
    int i = 0;
    for (auto it = ErrorMessages.begin(); it != ErrorMessages.end(); ++it, ++i)
    {
        char* m = os_strdup(gettext(it->second));
        int n = strlen(m);

        if (n && m[n-1] == '\n') m[n-1] = '\0'; // strip trailing \n
        msgs->set(i, m);
        FREE(m);

        if (num)
        {
            num->set(i, it->first);
        }
    }
    
    out.push_back(msgs);
    if (num)
    {
        out.push_back(num);
    }
    
    return Function::OK;
}
