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
#ifndef __GW_CORE__
#define __GW_CORE__
/*--------------------------------------------------------------------------*/
#include "machine.h"
#include "c_gateway_prototype.h"
/*--------------------------------------------------------------------------*/
int gw_core(void);
/*--------------------------------------------------------------------------*/
int C2F(sci_who)(char *fname, unsigned long fname_len);
int C2F(sci_return)(char *fname, unsigned long fname_len);
int C2F(sci_isdef)(char *fname, unsigned long fname_len);
STACK_GATEWAY_PROTOTYPE(C2F(sci_predef));
int C2F(sci_clearfun)(char *fname, unsigned long fname_len);
int C2F(sci_funptr)(char *fname, unsigned long fname_len);
int C2F(sci_whereis)(char *fname, unsigned long fname_len);
int C2F(sci_where)(char *fname, void* pvApiCtx);
int C2F(sci_what)(char *fname, unsigned long fname_len);
int C2F(sci_getos)(char *fname, unsigned long fname_len);
int C2F(sci_fromjava)(char *fname, unsigned long fname_len);
int C2F(sci_getmemory)(char *fname, unsigned long fname_len);
int C2F(sci_fromc)(char *fname, unsigned long fname_len);
int C2F(sci_getmodules)(char *fname, unsigned long fname_len);
int C2F(sci_with_module)(char *fname, unsigned long fname_len);
int C2F(sci_getscilabmode)(char *fname, unsigned long fname_len);
int C2F(sci_librarieslist)(char *fname, unsigned long fname_len);
int C2F(sci_funcprot)(char *fname, void* pvApiCtx);

//Scilab 6
STACK_GATEWAY_PROTOTYPE(sci_getdebuginfo);
/*--------------------------------------------------------------------------*/
#endif /*  __GW_CORE__ */
/*--------------------------------------------------------------------------*/

