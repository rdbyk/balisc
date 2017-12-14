/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2006 - INRIA - Allan CORNET
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
/*--------------------------------------------------------------------------*/
#ifndef __GW_ELEMENTARIES_FUNCTIONS__
#define __GW_ELEMENTARIES_FUNCTIONS__
/*--------------------------------------------------------------------------*/
#include "machine.h"
#include "dynlib_elementary_functions.h"
#include "c_gateway_prototype.h"
/*--------------------------------------------------------------------------*/

STACK_GATEWAY_PROTOTYPE(sci_nearfloat);
STACK_GATEWAY_PROTOTYPE(sci_number_properties);
STACK_GATEWAY_PROTOTYPE(sci_testmatrix);
STACK_GATEWAY_PROTOTYPE(sci_base2dec);
STACK_GATEWAY_PROTOTYPE(sci_dec2base);
C_GATEWAY_PROTOTYPE(sci_isvector);
C_GATEWAY_PROTOTYPE(sci_issquare);

#endif /*  __GW_ELEMENTARIES_FUNCTIONS__ */
/*--------------------------------------------------------------------------*/

