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

#include <stdio.h>
#include "function.hxx"
#include "string.hxx"
#include "double.hxx"
#include "file.hxx"
#include "filemanager.hxx"
#include "configvariable.hxx"
#include "fileio_gw.hxx"

extern "C"
{
#include "Scierror.h"
#include "Sciwarning.h"
#include "localization.h"
}

using types::Double;
using types::File;
using types::Function;
using types::String;
using types::typed_list;

static const char fname[] = "fflush";

Function::ReturnValue sci_fflush(typed_list &in, int _iRetCount, typed_list &out)
{
    int iFileID = 0;

    if (in.size() == 0)
    {
        iFileID = FileManager::getCurrentFile();
    }
    else if (in.size() == 1)
    {
        if (in[0]->isDouble())
        {
            Double* d = in[0]->getAs<Double>();
            
            if (d->getSize() != 1 || d->isComplex())
            {
                Scierror(999, _("%s: Wrong type for input argument #%d: A real expected.\n"), fname, 1);
                return Function::Error;
            }

            iFileID = static_cast<int>(d->getFirst());
            
            if (iFileID < 0)
            {
                Scierror(999, _("%s: Invalid file descriptor: %d.\n"), fname, iFileID);
                return Function::Error;
            }
        }
        else
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: An integer expected.\n"), fname, 1);
            return Function::Error;
        }
    }
    else
    {
        Scierror(999, _("%s: Wrong number of input arguments: %d or %d expected.\n"), fname, 0, 1);
        return Function::Error;
    }

    File* f = FileManager::getFile(iFileID);
    int ret = 0;

    if (f)
    {
        switch(f->getFileType())
        {
            case 2:
            case 3:
            case 4:
                ret = fflush(f->getFiledesc());
                break;

            default:
                // FIXME: do nothing?
                break;
        }
    }
    else if (ConfigVariable::getWarningMode())
    {
        Sciwarning(_("%s: Cannot flush file whose descriptor is %d: File is not active.\n"), fname, iFileID);
    }

    out.push_back(new Double(static_cast<double>(ret)));

    return Function::OK;
}
