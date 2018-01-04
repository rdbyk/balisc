// Balisc (https://github.com/rdbyk/balisc/)
// 
// Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
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

#include "graphics_gw.hxx"
#include "function.hxx"
#include "double.hxx"
#include "graphichandle.hxx"

extern "C"
{
#include "sci_types.h"
#include "Scierror.h"
#include "GetHashTable.h"
#include "SetHashTable.h"
#include "FigureList.h"
#include "HandleManagement.h"
}

using types::Function;
using types::InternalType;
using types::Double;
using types::GraphicHandle;

Function::ReturnValue sci_scf(types::typed_list &in, int _iRetCount, types::typed_list &out)
{
    int nin = in.size();
    
    if (nin == 0)
    {
        double h = (double)getValidDefaultFigureId();
        
        callSetProperty(NULL, 0, &h, sci_matrix, 1, 1, "current_figure");
        
        InternalType* res = static_cast<InternalType*>(callGetProperty(NULL, 0, "current_figure"));
        
        if (res)
        {
            out.push_back(res);
            return Function::OK;
        }
        else
        {
            return Function::Error;
        }
    }
    else if (nin == 1)
    {
        InternalType* h = in[0];
        
        if (h->isDouble())
        {
            Double* dh = h->getAs<Double>();

            if (dh->isScalar() == false)
            {
                Scierror(202, _("%s: Wrong size for argument #%d: A real scalar expected.\n"), "scf", 1);
                return Function::Error;
            }

            callSetProperty(NULL, 0, dh->get(), sci_matrix, 1, 1, "current_figure");

            InternalType* res = static_cast<InternalType*>(callGetProperty(NULL, 0, "current_figure"));
            
            if (res)
            {
                out.push_back(res);
                return Function::OK;
            }
            else
            {
                return Function::Error;
            }
        }
        else if (h->isHandle())
        {
            GraphicHandle* gh = h->getAs<GraphicHandle>();

            if (gh->isScalar() == false)
            {
                Scierror(202, _("%s: Wrong size for argument #%d: A single graphic handle expected.\n"), "scf", 1);
                return Function::Error;
            }
            
            int iObjUID = getObjectFromHandle(gh->getFirst());
            
            if (iObjUID == 0)
            {
                Scierror(999, _("%s: The handle is not or no more valid.\n"), "scf");
                return Function::Error;
            }
            
            callSetProperty(NULL, 0, gh->get(), sci_handles, 1, 1, "current_figure");

            InternalType* res = static_cast<InternalType*>(callGetProperty(NULL, 0, "current_figure"));
            
            if (res)
            {
                out.push_back(res);
                return Function::OK;
            }
            else
            {
                return Function::Error;
            }
        }
        else
        {
            Scierror(202, _("%s: Wrong type for argument #%d: real scalar or graphic handle expected.\n"), "scf", 1);
            return Function::Error;
        }
    }
    else
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d to %d expected.\n"), "scf", 0, 1);
        return Function::Error;
    }
}
