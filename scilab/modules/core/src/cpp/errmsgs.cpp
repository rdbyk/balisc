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

#include <map>
#include "errmsgs.h"

extern "C"
{
#include "localization.h"
}

#undef _
#define _(String) String

static const std::map<int, const char*> errmsgs = 
{
    { 0, _("Unknown error.\n") },
    { 1, _("No more memory.\n") },
    { 2, _("Invalid index.\n") },
    
    { 30, _("Wrong file descriptor: %d.\n") },
    { 31, _("Cannot read file %d.\n") },
    { 32, _("Cannot open file %s.\n") },
    { 33, _("Too many files opened!\n") },
    { 34, _("invalid filename %s.\n") },
    { 35, _("invalid status.\n") },

    { 70, _("Wrong number of input arguments.\n") },
    { 71, _("Wrong number of input arguments: %d expected.\n") },
    { 72, _("Wrong number of input arguments: %d to %d expected.\n") },
    { 73, _("Wrong number of input arguments: %d or %d expected.\n") },
    { 74, _("Wrong number of input arguments: at least %d expected.\n") },

    { 80, _("Wrong number of output arguments.\n") },
    { 81, _("Wrong number of output arguments: %d expected.\n") },
    { 82, _("Wrong number of output arguments: %d to %d expected.\n") },

    { 90, _("Wrong type for input argument #%d: %s expected.\n") },
    { 91, _("Wrong type for input argument #%d: string expected.\n") },
    { 92, _("Wrong type for input argument #%d: integer expected.\n") },
    { 93, _("Wrong type for input argument #%d: real scalar expected.\n") },
    { 94, _("Wrong type for input argument #%d: real matrix expected.\n") },
    { 95, _("Wrong type for input argument #%d: real or complex matrix expected.\n") },

    { 100, _("Wrong size for input argument #%d: %s expected.\n") },
    { 101, _("Wrong size for input argument #%d: real scalar expected.\n") },
    { 102, _("Wrong size for input argument #%d: string expected.\n") },
    { 103, _("Wrong size for input argument #%d: square matrix expected.\n") },
    
    { 110, _("Wrong value for input argument #%d: %s expected.\n") },
    { 111, _("Wrong value for input argument #%d: integer value expected.\n") },
};

char* ErrorMessageByNumber(int n)
{
    auto it = errmsgs.find(n);

    if (it != errmsgs.end())
    {
        return gettext(it->second);
    }
    else
    {
        return nullptr;
    }
}
