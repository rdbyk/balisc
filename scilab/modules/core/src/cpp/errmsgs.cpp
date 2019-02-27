// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2018 - 2019 Dirk Reusch, Kybernetik Dr. Reusch
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
    { 3, _("Inconsistent row/column dimensions.\n") },
    { 4, _("Redefining permanent variable.\n") },
    { 5, _("Incompatible output argument.\n") },
    { 6, _("Submatrix incorrectly defined.\n") },
    { 7, _("Wrong insertion : Cannot insert without arguments.\n") },
    { 8, _("Cell indexing \"{..}\" of non-cell objects is not allowed.\n") },
    { 9, _("Attempt to reference field of non-structure array.\n") },
    { 10, _("Fields evaluation failed.\n") },
    { 11, _("Wrong insertion: A Cell expected: use {...} instead of (...).\n") },
    { 12, _("Get fields from expression failed.\n") },
    { 13, _("Unable to extract right part expression.\n") },
    { 14, _("for expression : Wrong type for loop iterator.\n") },
    { 15, _("for expression can only manage 1 or 2 dimensions variables.\n") },
    { 16, _("for expression : No value for assignment to loop variable.\n") },
    { 17, _("%s: Redefining function '%s'. Use 'funcprot(0)' to avoid this message.\n") },
    { 18, _("Unable to insert multiple item in a Struct.\n") },
    { 19, _("Unable to insert multiple item in a List.\n") },
    { 20, _("Unknown expression.\n") },
    { 21, _("Wrong insertion.\n") },
    { 22, _("Recursion limit exceeded. Use 'recursionlimit' to increase it.\n") },
    { 23, _("Overloaded operator does not return a result.\n") },
    { 24, _("Not implemented.\n") },
    { 25, _("With input arguments, return expects output arguments.\n") },
    { 26, _("function is disabled in -nogui or -nwni mode.\n") },
    { 27, _("Evaluation of element in cell expression failed.\n") },
    { 28, _("Indexing not allowed for output arguments of return.\n") },
    { 29, _("Can not assign multiple value in a single variable.\n") },
    { 30, _("Unknown script form.\n") },
    { 31, _("Instruction left hand side: waiting for a name.\n") },
    { 32, _("Left side of optional parameter must be a variable.\n") },
    { 33, _("Cannot extract from nothing.\n") },
    { 34, _("Index value exceeds maximum of 2147483647.\n") },
    { 35, _("Assignment between unlike types is not allowed.\n") },
    { 36, _("Division by zero...\n") },
    { 37, _("Invalid exponent.\n") },
    { 38, _("Invalid exponent: expected finite integer exponents.\n") },
    { 39, _("With NaN or Inf a division by scalar expected.\n") },
    { 40, _("Undefined variable: '%s'.\n") },
    { 41, _("'%s': Wrong type for operand #%d: real scalar expected.\n") },
    { 42, _("'%s': Evaluation of operand #%d yields no result.\n") },
    { 43, _("Wrong type for 'varargout': list expected.\n") },
    { 44, _("Element #%d in 'varargout' is undefined.\n") },
    { 45, _("An error has been detected while loading %s: %s.\n") },
    { 45, _("Impossible to load %s library.\n") },
    { 46, _("Impossible to load %s function in %s library: %s.\n") },
    { 47, _("Can not read input argument #%d.\n") },
    { 48, _("Can not apply \"'\" to several elements.\n") },
    { 49, _("Not enough values for assignation to several variables.\n") },

    // fileio
    { 50, _("Wrong file descriptor: %d.\n") },
    { 51, _("Cannot read file %d.\n") },
    { 52, _("Cannot open file %s.\n") },
    { 53, _("Too many files opened!\n") },
    { 54, _("invalid filename %s.\n") },
    { 55, _("invalid status.\n") },
    { 56, _("Invalid format.\n") },

    { 70, _("Wrong number of input arguments.\n") },
    { 71, _("Wrong number of input arguments: %d expected.\n") },
    { 72, _("Wrong number of input arguments: %d to %d expected.\n") },
    { 73, _("Wrong number of input arguments: %d or %d expected.\n") },
    { 74, _("Wrong number of input arguments: at least %d expected.\n") },
    { 75, _("Wrong number of input arguments: at most %d expected.\n") },
    { 76, _("Wrong number of input arguments: %s expected.\n") },

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

    // localization
    { 120, _("Unable to add new domain %s.\n") },

    // hdf5
    { 130, _("Invalid H5Object.\n") },
    { 131, _("Cannot remove H5Object.\n") },
    { 132, _("HDF5 exception '%s' caught.\n") },

    // console
    { 140, _("Not implemented in mode '%s'.\n") },

    // output_stream
    { 150, _("Number or types of input arguments do not match format.\n") },

    // xml
    { 160, _("%s does not exist.\n") },
    { 161, _("Unknown field: %s.\n") },
    { 162, _("Wrong type to set %s field.\n") },
    { 163, _("Field %s is not modifiable.\n") },
    { 164, _("Error in getting rhs argument.\n") },
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
