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
    { 17, _("Unexpected redefinition of Scilab function.\n") },
    { 18, _("Unable to insert multiple item in a Struct.\n") },
    { 19, _("Unable to insert multiple item in a List.\n") },
    { 20, _("Unknown expression.\n") },
    { 21, _("Wrong insertion.\n") },
    { 22, _("Wrong insertion in a Cell.\n") },
    { 23, _("Overloaded operator does not return a result.\n") },
    { 24, _("Not implemented.\n") },
    { 25, _("With input arguments, return expects output arguments.\n") },
    { 26, _("/!\\ Unmanaged FieldExp.\n") },
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
    
    { 50, _("Wrong file descriptor: %d.\n") },
    { 51, _("Cannot read file %d.\n") },
    { 52, _("Cannot open file %s.\n") },
    { 53, _("Too many files opened!\n") },
    { 54, _("invalid filename %s.\n") },
    { 55, _("invalid status.\n") },

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
