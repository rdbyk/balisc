/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2009 - DIGITEO - Allan CORNET
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

#include "transposeMatrix.h"
#include "sci_malloc.h"

double *transposeMatrixDouble(int C, int L, double *MatrixDouble)
{
    double *buffer = NULL;
    if (MatrixDouble)
    {
        buffer = (double *)MALLOC( (C * L) * sizeof(double) );
        if (buffer)
        {
            int i = 0;
            int j = 0;

            for (i = 0; i < C; i++) for (j = 0; j < L; j++)
                {
                    buffer[ i * L + j ] = MatrixDouble[ j * C + i ];
                }
        }
    }
    return buffer;
}
