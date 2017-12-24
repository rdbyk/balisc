/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Allan CORNET
 * Copyright (C) DIGITEO - 2009 - Allan CORNET
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

#ifndef __ISLETTER_H__
#define __ISLETTER_H__

#include <wchar.h>
#include "BOOL.h"

/**
* array elements that are alphabetic letters
* @param[in] a string
* @return BOOL array
*/
BOOL *isletter(char *input_string, int *sizeArray);
BOOL *isletterW(wchar_t *wcInput_string, int *sizeArray);

#endif /* __ISLETTER_H__ */
