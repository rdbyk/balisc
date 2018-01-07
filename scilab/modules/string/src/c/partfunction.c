/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2008 - INRIA - Allan CORNET
 * Copyright (C) 2012 - 2016 - Scilab Enterprises
 * Copyright (C) 2017 - 2018 Dirk Reusch, Kybernetik Dr. Reusch
 *
 * This file is hereby licensed under the terms of the GNU GPL v2.0,
 * pursuant to article 5.3.4 of the CeCILL v.2.1.
 * This file was originally licensed under the terms of the CeCILL v2.1,
 * and continues to be available under such terms.
 * For more information, see the COPYING file which you should have received
 * along with this program.
 *
 */

#include <string.h>
#include "sci_malloc.h"
#include "partfunction.h"
#include "freeArrayOfString.h"
#include "charEncoding.h"

wchar_t **partfunctionW(wchar_t** _pwstStringInput, const int _iSize, const int *_piVectInput, const int _iVectSize)
{
    wchar_t** pwstParts = (wchar_t**)MALLOC(sizeof(wchar_t*) * (_iSize));

    int i;
    for (i = 0 ; i < _iSize ; i++)
    {
        int len_StringInput_i = wcslen(_pwstStringInput[i]);
        
        pwstParts[i] = (wchar_t*)MALLOC(sizeof(wchar_t) * (_iVectSize + 1));
        
        int j;
        for (j = 0 ; j < _iVectSize ; j++)
        {
            if (_piVectInput[j] > len_StringInput_i)
            {
                pwstParts[i][j] = L' ';
            }
            else
            {
                pwstParts[i][j] = _pwstStringInput[i][_piVectInput[j] - 1];
            }
        }
        pwstParts[i][_iVectSize] = L'\0';
    }
    return pwstParts;
}

