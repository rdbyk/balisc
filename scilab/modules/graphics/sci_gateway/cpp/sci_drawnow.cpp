// Balisc (https://github.com/rdbyk/balisc/)
//
// Copyright (C) 2006 - INRIA - Fabrice Leray
// Copyright (C) 2006 - INRIA - Jean-Baptiste Silvy
// Copyright (C) 2012 - 2016 - Scilab Enterprises
// Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
//
// This file is hereby licensed under the terms of the GNU GPL v2.0,
// pursuant to article 5.3.4 of the CeCILL v.2.1.
// This file was originally licensed under the terms of the CeCILL v2.1,
// and continues to be available under such terms.
// For more information, see the COPYING file which you should have received
// along with this program.

#include "graphics_gw.hxx"
#include "function.hxx"

extern "C"
{
#include "Scierror.h"
#include "localization.h"
#include "BuildObjects.h"
#include "CurrentObject.h"
#include "getGraphicObjectProperty.h"
#include "setGraphicObjectProperty.h"
#include "graphicObjectProperties.h"
}

using types::Function;
using types::typed_list;

Function::ReturnValue sci_drawnow(typed_list &in, int _iRetCount, typed_list &out)
{
    if (in.size() != 0)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), "drawnow", 0);
        return Function::Error;
    }

    int iSubwinUID = getOrCreateDefaultSubwin();

    if (iSubwinUID != 0)
    {
        int iType = -1;
        int *piType = &iType;
        
        // Look for top level figure
        int iCurChildUID = iSubwinUID;
        int iParentFigureUID = 0;

        do
        {
            iParentFigureUID = getParentObject(iCurChildUID);
            getGraphicObjectProperty(iParentFigureUID, __GO_TYPE__, jni_int, (void **)&piType);
            iCurChildUID = iParentFigureUID;
        }
        while (iParentFigureUID != 0 && iType != __GO_FIGURE__);

        int iTrue = (int)TRUE;

        if (iParentFigureUID != 0)
        {
            setGraphicObjectProperty(iParentFigureUID, __GO_IMMEDIATE_DRAWING__, &iTrue, jni_bool, 1);
        }
    }

    return Function::OK;
}
