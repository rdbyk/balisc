// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2019 - Dirk Reusch, Kybernetik Dr. Reusch
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

#include "functions_gw.hxx"
#include "double.hxx"
#include "string.hxx"
#include "macro.hxx"
#include "macrofile.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
}

using types::Double;
using types::Function;
using types::InternalType;
using types::MacroFile;
using types::String;
using types::typed_list;

types::Function::ReturnValue sci_macrofile(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 1)
    {
        Scierror(71 , 1);
        return Function::Error;
    }

    switch (in[0]->getType())
    {
        case InternalType::ScilabMacro:
            out.push_back(Double::Empty());
            return Function::OK;

        case InternalType::ScilabMacroFile:
        {
            std::wstring path = in[0]->getAs<MacroFile>()->getPath();
            //path.replace(path.end() - 4, path.end(), L".sci");
            out.push_back(new String(path.replace(path.end() - 4, path.end(), L".sci").c_str()));
            return Function::OK;
        }

        default :
            Scierror(90, 1, _("macro"));
            return Function::Error;
    }
}
