/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2011 - DIGITEO - Allan CORNET
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
#ifndef __CSV_ISNUM_H__
#define __CSV_ISNUM_H__

#include "BOOL.h"
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

BOOL isNum(const char *pStr);
BOOL *isNumMatrix(const char **pStrs, int nbRows, int nbCols);
BOOL isNumW(const wchar_t *pStr);
BOOL *isNumMatrixW(const wchar_t **pStrs, int nbRows, int nbCols);

#ifdef __cplusplus
}
#endif

#endif /* __CSV_ISNUM_H__ */
