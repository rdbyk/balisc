/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2018 - Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#ifndef __SCIERROR__
#define __SCIERROR__

#include <stdarg.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "do_error_number.h"

#define bsiz 4096

int  Scierror(int iv, ...);

#ifdef __cplusplus
}
#endif

#endif /* __SCIERROR__ */
