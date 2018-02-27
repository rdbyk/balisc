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

#include "time_gw.hxx"
#include "double.hxx"
#include "string.hxx"
#include "function.hxx"

extern "C"
{
#include <time.h>
#include "Scierror.h"
#include "localization.h"
}

using types::Double;
using types::Function;
using types::String;
using types::typed_list;

static const char fname[] = "sleep";

Function::ReturnValue sci_sleep(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() < 1 || in.size() > 2)
    {
        Scierror(999, _("%s: Wrong number of input arguments: %d or %d expected.\n"), fname , 1, 2);
        return Function::Error;
    }

    if (in[0]->isDouble() == false)
    {
        
        Scierror(999, _("%s: Wrong type for input argument #%d: A real scalar expected.\n"), fname, 1);
        return Function::Error;
    }
    
    Double* d = in[0]->getAs<Double>();

    if (d->getSize() != 1)
    {
        
        Scierror(999, _("%s: Wrong size for input argument #%d: A real scalar expected.\n"), fname, 1);
        return Function::Error;
    }

    if (d->getFirst() <= 0.0)
    {
        
        Scierror(999, _("%s: Wrong value for input argument #%d: A positive real expected.\n"), fname, 1);
        return Function::Error;
    }

    struct timespec duration;

    if (in.size() == 2)
    {
        if (in[1]->isString() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: A single string expected.\n"), fname, 2);
            return Function::Error;
        }
        
        String* opt = in[1]->getAs<String>();
        
        if (opt->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: A single string expected.\n"), fname, 2);
            return Function::Error;
        }
        
        if (wcscmp(opt->getFirst(), L"s") != 0)
        {
            Scierror(999, _("%s: Wrong value for input argument #%d: 's' expected.\n"), fname, 2);
            return Function::Error;
        }

        int ms = static_cast<int>(d->getFirst() * 1000);
        duration.tv_sec = ms / 1000;
        duration.tv_nsec = (ms % 1000) * 1000000;
    }
    else
    {
        int us = static_cast<int>(d->getFirst() * 1000);
        duration.tv_sec = us / 1000000;
        duration.tv_nsec = (us % 1000000) * 1000;
    }
    
    nanosleep(&duration, NULL);

    return Function::OK;
}
