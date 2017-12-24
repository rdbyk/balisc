/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2007 - INRIA
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
#ifndef __MPUT_H__
#define __MPUT_H__

#include <stdio.h>
#include "machine.h"

/**
* mput functions  write data in a machine
* independant way (i.e write in little-endian)
* or can be used to write in little or big endian
*/
void C2F(mput) (int *fd, double *res, int *n, char *type, int *ierr);

void mput2 (FILE *fa, int swap2, double *res, int n, char *type, int *ierr);

#endif /* __MPUT_H__ */
/*--------------------------------------------------------------------------*/
