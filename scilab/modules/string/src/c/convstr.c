/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) INRIA - Cong WU
 * Copyright (C) INRIA - Allan CORNET
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
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include "convstr.h"
/*--------------------------------------------------------------------------*/
void convstr(wchar_t **Input_Matrix, wchar_t **Output_Matrix, char typ, int mn)
{
    int to_upper = (typ == L'u')||(typ == L'U');
    
    int x;
    for (x = 0 ; x < mn; x++)
    {
        size_t len_Input_Matrix = wcslen(Input_Matrix[x]);
        int y;
        for (y = 0; y < len_Input_Matrix; y++)
        {
            if (to_upper)
            {
                Output_Matrix[x][y] = (wchar_t)towupper(Input_Matrix[x][y]);
            }
            else
            {
                Output_Matrix[x][y] = (wchar_t)towlower(Input_Matrix[x][y]);
            }
        }
    }
}
/*--------------------------------------------------------------------------*/
