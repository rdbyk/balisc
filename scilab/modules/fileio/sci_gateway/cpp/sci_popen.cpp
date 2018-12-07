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

#include "function.hxx"
#include "string.hxx"
#include "double.hxx"
#include "file.hxx"
#include "filemanager.hxx"
#include "fileio_gw.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "charEncoding.h"
#include "sci_malloc.h"
}

using types::Double;
using types::File;
using types::Function;
using types::String;
using types::typed_list;

static const char fname[] = "popen";

Function::ReturnValue sci_popen(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() >= 1)
    {
        if (in[0]->isString() == false)
        {
            Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), fname, 1);
            return Function::Error;
        }

        String* pCommand = in[0]->getAs<String>();
     
        if (pCommand->getSize() != 1)
        {
            Scierror(999, _("%s: Wrong size for input argument #%d: string expected.\n"), fname , 1);
            return Function::Error;
        }
        
        String* pMode = new String(L"r");

        if (in.size() == 2)
        {
            if (in[1]->isString() == false)
            {
                Scierror(999, _("%s: Wrong type for input argument #%d: string expected.\n"), fname, 2);
                return Function::Error;
            }

            delete pMode;
            pMode = in[1]->getAs<String>();
            
            if (pMode->getSize() != 1)
            {
                Scierror(999, _("%s: Wrong size for input argument #%d: string expected.\n"), fname , 2);
                return Function::Error;
            }
        }
        else if (in.size() > 2)
        {
            Scierror(999, _("%s: Wrong number of input arguments: %d to %d expected.\n"), fname , 1, 2);
            return Function::Error;
        }

        char* mode = wide_string_to_UTF8(pMode->getFirst());
        char* command = wide_string_to_UTF8(pCommand->getFirst());
        
        FILE* fs = popen(command, mode);
        
        FREE(command);
        FREE(mode);
        
        if (fs)
        {
            File* pFile = new File();
            pFile->setFileDesc(fs);
            pFile->setFilename(pCommand->getFirst());
            pFile->setFileType(4); // pipe
            pFile->setFileMode(pMode->getFirst());
            pFile->setFileSwap(0);

            out.push_back(new Double(FileManager::addFile(pFile)));
            return Function::OK;
        }
        else
        {
            Scierror(999, _("%s: fork, pipe, or memory allocation failed.\n"), fname);
            return Function::Error;
        }
    }
    else
    {
        Scierror(999, _("%s: Wrong number of input arguments: %d to %d expected.\n"), fname , 1, 2);
        return Function::Error;
    }
}
