/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include "CallScilabBridge.hxx"
#include "configvariable.hxx"

extern "C"
{
#include "InitializeGUI.h"
#include "configvariable_interface.h" /* FIXME: enum scilabMode */
#include "getScilabJavaVM.h"
#ifdef _MSC_VER
#include "WindowShow.h"
#endif
}
/*--------------------------------------------------------------------------*/
BOOL InitializeGUI()
{
    if (ConfigVariable::getScilabMode() == SCILAB_STD)
    {

#ifdef _MSC_VER
        WindowShow();
#endif
    }
    else
    {
        if (getWebMode() == 0)
        {
            org_scilab_modules_gui_bridge::CallScilabBridge::registerSwingView(getScilabJavaVM());
        }

        return TRUE;
    }

    return FALSE;
}

/*--------------------------------------------------------------------------*/
