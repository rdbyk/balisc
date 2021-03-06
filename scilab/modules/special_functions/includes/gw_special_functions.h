/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) ????-2008 - INRIA
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

#ifndef __GW_SPECIAL_FUNCTIONS_H__
#define __GW_SPECIAL_FUNCTIONS_H__

int sci_besselh(char *fname, void* pvApiCtx);
int sci_besseli(char *fname, void* pvApiCtx);
int sci_besselj(char *fname, void* pvApiCtx);
int sci_besselk(char *fname, void* pvApiCtx);
int sci_bessely(char *fname, void* pvApiCtx);
int sci_beta(char *fname, void* pvApiCtx);
int sci_legendre(char *fname, void* pvApiCtx);
int sci_Faddeeva_erf(char *fname, void* pvApiCtx);
int sci_Faddeeva_erfc(char *fname, void* pvApiCtx);
int sci_Faddeeva_erfcx(char *fname, void* pvApiCtx);
int sci_Faddeeva_erfi(char *fname, void* pvApiCtx);
int sci_Faddeeva_dawson(char *fname, void* pvApiCtx);

#endif /* __GW_SPECIAL_FUNCTIONS_H__ */
