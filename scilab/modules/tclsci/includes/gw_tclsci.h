/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2005-2008 - INRIA - Allan CORNET
 * Copyright (C) 2007-2008 - INRIA - Vincent COUVERT
 * Copyright (C) 2007-2008 - INRIA - Bruno JOFRET
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

#ifndef __GW_TCLSCI__
#define __GW_TCLSCI__

#include "c_gateway_prototype.h"

STACK_GATEWAY_PROTOTYPE(sci_TCL_EvalStr);
STACK_GATEWAY_PROTOTYPE(sci_TCL_ExistInterp);
STACK_GATEWAY_PROTOTYPE(sci_TCL_GetVar);
STACK_GATEWAY_PROTOTYPE(sci_TCL_DoOneEvent);
STACK_GATEWAY_PROTOTYPE(sci_TCL_EvalFile);
STACK_GATEWAY_PROTOTYPE(sci_TCL_SetVar);
STACK_GATEWAY_PROTOTYPE(sci_TCL_ExistVar);
STACK_GATEWAY_PROTOTYPE(sci_TCL_ExistArray);
STACK_GATEWAY_PROTOTYPE(sci_opentk);
STACK_GATEWAY_PROTOTYPE(sci_TCL_GetVersion);
STACK_GATEWAY_PROTOTYPE(sci_TCL_UnsetVar);
STACK_GATEWAY_PROTOTYPE(sci_TCL_UpVar);
STACK_GATEWAY_PROTOTYPE(sci_TCL_CreateSlave);
STACK_GATEWAY_PROTOTYPE(sci_TCL_DeleteInterp);

#endif /*  __GW_TCLSCI__ */
